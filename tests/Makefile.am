AM_CPPFLAGS = -I. -I$(top_builddir) -I$(top_srcdir)
AM_CFLAGS = -std=gnu17 -Wall -pedantic -Werror=implicit

check_PROGRAMS = strlists

strlists_SOURCES = strlists.c
strlists_LDADD = $(top_builddir)/libecc/libecc.a

TESTS = \
	$(check_PROGRAMS)
