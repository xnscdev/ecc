#
# This file is part of ECC.
# Copyright (C) 2020 XNSC
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.
#

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
