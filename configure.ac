# mathlib library version information
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# (shamelessly stolen from GiNaC (http://www.ginac.de/)
# Making releases:
#   mathlib_micro_version += 1;
#   mathlib_interface_age += 1;
#   mathlib_binary_age += 1;
# if any functions have been added, set mathlib_interface_age to 0.
# if backwards compatibility has been broken,
# set mathlib_binary_age and gaol_interface_age to 0.
# Version information for mathlib
m4_define([mathlib_major_version], [2])
m4_define([mathlib_minor_version], [1])
m4_define([mathlib_micro_version], [0])
m4_define([mathlib_version], ["mathlib_major_version.mathlib_minor_version.mathlib_micro_version"])
m4_define([mathlib_release], [mathlib_major_version.mathlib_minor_version])
m4_define([mathlib_interface_age], [0])
m4_define([mathlib_binary_age], [0])
dnl Version number. Do not forget to modify it also in AC_INIT() below
MATHLIB_MAJOR_VERSION=2
MATHLIB_MINOR_VERSION=1
MATHLIB_PATCH_VERSION=0
MATHLIB_RPM_RELEASE=1
MATHLIB_VERSION=${MATHLIB_MAJOR_VERSION}.${MATHLIB_MINOR_VERSION}.${MATHLIB_PATCH_VERSION}
AC_SUBST(MATHLIB_MAJOR_VERSION)
AC_SUBST(MATHLIB_MINOR_VERSION)
AC_SUBST(MATHLIB_MICRO_VERSION)
AC_SUBST(MATHLIB_RPM_RELEASE)

dnl Using a literal for the version number here, since
dnl newer versions of autoconf do not allow shell substitutions
AC_INIT([mathlib],[2.1.0])
AC_CONFIG_SRCDIR(src/MathLib.h)
dnl AC_PREREQ(2.13)

AM_MAINTAINER_MODE([disable])

AC_CONFIG_MACRO_DIR([m4])

dnl libtool versioning
m4_define([lt_revision], [mathlib_interface_age])
m4_define([lt_current], [m4_eval(mathlib_micro_version - mathlib_interface_age)])
m4_define([lt_age], [m4_eval(mathlib_binary_age - mathlib_interface_age)])
LT_VERSION_INFO="lt_current:lt_revision:lt_age"
LT_RELEASE="mathlib_release"

AC_SUBST(LT_VERSION_INFO)
AC_SUBST(LT_RELEASE)

LT_PREREQ([2.2.6])
LT_INIT([dlopen])


dnl options
AC_ARG_WITH(xlc,[ --with-xlc	Under AIX, use the xlc even if gcc exists])

AM_CONFIG_HEADER(src/mathlib_configuration.h)
AM_INIT_AUTOMAKE

dnl AC_PROG_MAKE_SET

dnl Determines the kind of architecture to use
AC_CANONICAL_HOST

# Testing existence of "-mpc64" compiler option

case "$host$" in
i?86-*-linux*)
	AC_DEFINE(MATHLIB_LINUX,1,
	          [Define this if your system is a linux based ix86 or compatible])
	AC_DEFINE(IX86_CPU,1,
				[Define this if your system is ix86-based]) 
	;;
*86_64-*-linux*)
	AC_DEFINE(MATHLIB_LINUX,1,
	          [Define this if your system is a linux based ix86 or compatible])
	AC_DEFINE(X86_64BITS,1,
		  [Define this if the OS is a 64 bits one])
	AC_DEFINE(IX86_CPU,1,
				[Define this if your system is ix86-based]) 
	;;
i?86-*-cygwin*)
	AC_DEFINE(MATHLIB_CYGWIN,1,
	          [Define this if your system is a cygwin based ix86 or compatible])
	AC_DEFINE(IX86_CPU,1,
				[Define this if your system is ix86-based]) 
	;;
i?86-apple*)
	AC_DEFINE(MATHLIB_I86_MACOSX,1,
				[Define this if your system is a ix86 running MacOSX])
	AC_DEFINE(IX86_CPU,1,
				[Define this if your system is ix86-based]) 
	;;
rs6000-* | powerpc-*)
	AC_DEFINE(MATHLIB_AIX,1,
	          [Define this if your system is AIX based])
	;;
*-sun-*)
	AC_DEFINE(MATHLIB_SUN,1,
	          [Define this if your system is SUN based])
	;;
*)
	AC_MSG_ERROR(Sorry, this system is not yet supported by mathlib)
esac

AC_CHECK_HEADERS([fenv.h])

CFLAGS="-g0 -O2 $CFLAGS"

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_PROG_MKDIR_P

AC_OUTPUT([Makefile src/Makefile mathlib.spec])
