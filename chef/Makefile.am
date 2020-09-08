AM_CPPFLAGS = -I. -I$(top_builddir) -I$(top_srcdir)
AM_CFLAGS = -std=gnu17 -Wall -pedantic -Werror=implicit
AM_YFLAGS = -d -Wno-yacc
BUILT_SOURCES = chef-parser.h

bin_PROGRAMS = chef
chef_SOURCES = chef.c chef.h gen.c chef-lexer.l chef-parser.y
chef_LDADD = $(top_builddir)/libecc/libecc.a
