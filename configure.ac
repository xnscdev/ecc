AC_INIT([ECC], [1.1], [xpm@linuxmail.org])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

AC_PROG_CC
AC_PROG_RANLIB
AC_PROG_LEX
AC_PROG_YACC

if ! ($YACC --version 2>/dev/null | grep -q bison); then
    AC_MSG_ERROR([yacc does not appear to be GNU bison])
fi

PKG_CHECK_MODULES([BDW_GC], [bdw-gc], [],
[AC_MSG_ERROR([bdw-gc required but not found])])
AC_SUBST([BDW_GC_CFLAGS])
AC_SUBST([BDW_GC_LIBS])
LIBS="$LIBS $BDW_GC_LIBS"

AC_CHECK_LIB([gccjit], [gcc_jit_context_acquire], [LIBS="$LIBS -lgccjit"],
[AC_MSG_ERROR([libgccjit required but not found])])
AC_CHECK_HEADER([libgccjit.h], [],
[AC_MSG_ERROR([libgccjit.h header not found])])

AC_CONFIG_FILES([
	Makefile
	chef/Makefile
	libecc/Makefile
	tests/Makefile
])
AC_OUTPUT
