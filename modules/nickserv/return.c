/*
 * Copyright (c) 2005 Alex Lambert
 * Rights to this code are as documented in doc/LICENSE.
 *
 * Implements nickserv RETURN.
 */

#include "atheme.h"
#include "authcookie.h"

static void
ns_cmd_return(struct sourceinfo *si, int parc, char *parv[])
{
	char *target = parv[0];
	char *newmail = parv[1];
	char *newpass;
	char oldmail[EMAILLEN + 1];
	struct myuser *mu;
	struct user *u;
	mowgli_node_t *n, *tn;

	if (!target || !newmail)
	{
		command_fail(si, fault_needmoreparams, STR_INSUFFICIENT_PARAMS, "RETURN");
		command_fail(si, fault_needmoreparams, _("Usage: RETURN <account> <e-mail address>"));
		return;
	}

	if (!(mu = myuser_find(target)))
	{
		command_fail(si, fault_nosuch_target, _("\2%s\2 is not registered."), target);
		return;
	}

	if (is_soper(mu))
	{
		logcommand(si, CMDLOG_ADMIN, "failed RETURN \2%s\2 to \2%s\2 (is SOPER)", target, newmail);
		command_fail(si, fault_badparams, _("\2%s\2 belongs to a services operator; it cannot be returned."), target);
		return;
	}

	if (!validemail(newmail))
	{
		command_fail(si, fault_badparams, _("\2%s\2 is not a valid e-mail address."), newmail);
		return;
	}

	newpass = random_string(12);
	mowgli_strlcpy(oldmail, mu->email, sizeof oldmail);
	myuser_set_email(mu, newmail);

	if (!sendemail(si->su != NULL ? si->su : si->service->me, mu, EMAIL_SENDPASS, mu->email, newpass))
	{
		myuser_set_email(mu, oldmail);
		command_fail(si, fault_emailfail, _("Sending email failed, account \2%s\2 remains with \2%s\2."),
				entity(mu)->name, mu->email);
		sfree(newpass);
		return;
	}

	set_password(mu, newpass);

	sfree(newpass);

	// prevents users from "stealing it back" in the event of a takeover
	metadata_delete(mu, "private:verify:emailchg:key");
	metadata_delete(mu, "private:verify:emailchg:newemail");
	metadata_delete(mu, "private:verify:emailchg:timestamp");
	metadata_delete(mu, "private:setpass:key");
	metadata_delete(mu, "private:sendpass:sender");
	metadata_delete(mu, "private:sendpass:timestamp");

	// log them out
	MOWGLI_ITER_FOREACH_SAFE(n, tn, mu->logins.head)
	{
		u = (struct user *)n->data;
		if (!ircd_logout_or_kill(u, entity(mu)->name))
		{
			u->myuser = NULL;
			mowgli_node_delete(n, &mu->logins);
			mowgli_node_free(n);
		}
	}
	mu->flags |= MU_NOBURSTLOGIN;
	authcookie_destroy_all(mu);

	wallops("%s returned the account \2%s\2 to \2%s\2", get_oper_name(si), target, newmail);
	logcommand(si, CMDLOG_ADMIN | LG_REGISTER, "RETURN: \2%s\2 to \2%s\2", target, newmail);
	command_success_nodata(si, _("The e-mail address for \2%s\2 has been set to \2%s\2"),
						target, newmail);
	command_success_nodata(si, _("A random password has been set; it has been sent to \2%s\2."),
						newmail);
}

static struct command ns_return = {
	.name           = "RETURN",
	.desc           = N_("Returns an account to its owner."),
	.access         = PRIV_USER_ADMIN,
	.maxparc        = 2,
	.cmd            = &ns_cmd_return,
	.help           = { .path = "nickserv/return" },
};

static void
mod_init(struct module ATHEME_VATTR_UNUSED *const restrict m)
{
	service_named_bind_command("nickserv", &ns_return);
}

static void
mod_deinit(const enum module_unload_intent ATHEME_VATTR_UNUSED intent)
{
	service_named_unbind_command("nickserv", &ns_return);
}

SIMPLE_DECLARE_MODULE_V1("nickserv/return", MODULE_UNLOAD_CAPABILITY_OK)
