AC_PREREQ([2.69])
AC_INIT([cutil], [0.1.0], [caaallum])

AM_INIT_AUTOMAKE([1.9.6 -Wall -Werror subdir-objects dist-xz])

AC_PROG_CC
AM_PROG_AR
AC_PATH_PROG(TAR, tar, /bin/tar)
AC_PROG_INSTALL
LT_INIT

PKG_CHECK_MODULES([CHECK], [check])

AC_CONFIG_FILES([Makefile src/Makefile check/Makefile])

AC_OUTPUT
