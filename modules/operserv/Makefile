# Copyright (c) 2003-2004 E. Will et al.
# Rights to this code are documented in doc/LICENSE.

MODULE		= operserv

SRCS =			\
	akill.c		\
	clearchan.c	\
	clones.c	\
	compare.c	\
	genhash.c	\
	greplog.c	\
	help.c		\
	identify.c	\
	ignore.c	\
	info.c		\
	inject.c	\
	jupe.c		\
	main.c		\
	mode.c		\
	modinspect.c	\
	modlist.c	\
	modload.c	\
	modreload.c	\
	modunload.c	\
	noop.c		\
	override.c	\
	raw.c		\
	rakill.c	\
	readonly.c	\
	rmatch.c	\
	rehash.c	\
	restart.c	\
	rnc.c		\
	rwatch.c	\
	set.c		\
	shutdown.c	\
	sgline.c	\
	soper.c		\
	specs.c		\
	sqline.c	\
	uptime.c	\
	update.c

include ../../extra.mk
include ../../buildsys.mk
include ../../buildsys.module.mk

CPPFLAGS	+= -I../../include
LDFLAGS		+= -L../../libathemecore
LIBS		+= -lathemecore
