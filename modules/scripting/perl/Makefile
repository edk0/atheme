# Copyright (c) 2010 Atheme Development Group
# Rights to this code are documented in doc/LICENSE.

PLUGIN		= perl$(PLUGIN_SUFFIX)
SUBDIRS		= api
SRCS		= perl_module.c perl_object_list.c perlxsi.c

include ../../../extra.mk
include ../../../buildsys.mk

plugindir	= $(MODDIR)/modules/scripting

CPPFLAGS	+= -I../../../include -I. -DPERL_MODDIR=\"$(plugindir)\" $(PERL_CFLAGS)
LDFLAGS		+= -L../../../libathemecore
LIBS		+= -lathemecore $(PERL_LIBS)

CFLAGS		+= $(PLUGIN_CFLAGS)
LDFLAGS		+= $(PLUGIN_LDFLAGS)

# Disable warnings on the Perl code; Perl's system headers are *garbage*
CFLAGS		+= -w

perlxsi.c:
	perl -MExtUtils::Embed -e xsinit

install-extra:
	${MKDIR_P} '${DESTDIR}'${plugindir}/lib
	${INSTALL} -m644 lib/*.pl lib/*.pm '${DESTDIR}'${plugindir}/lib
	${MKDIR_P} '${DESTDIR}'${plugindir}/lib/Atheme
	${INSTALL} -m644 lib/Atheme/*.pm '${DESTDIR}'${plugindir}/lib/Atheme
	${MKDIR_P} '${DESTDIR}'${plugindir}/lib/Atheme/Internal
	${INSTALL} -m644 lib/Atheme/Internal/*.pm '${DESTDIR}'${plugindir}/lib/Atheme/Internal
	${MKDIR_P} '${DESTDIR}'${plugindir}/examples
	${INSTALL} -m644 examples/*.pl '${DESTDIR}'${plugindir}/examples
