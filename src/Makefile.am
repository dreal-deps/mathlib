EXTRA_DIST = asincos.tbl  root.tbl    uatan.tbl  uexp.tbl  upow.tbl \
	     powtwo.tbl   sincos.tbl  ucot.tbl   ulog.tbl  utan.tbl \
	     LINUX_DPChange.c LINUX64_DPChange.c SUN_DPChange.c AIX_DPChange.c IX86MACOSX_DPChange.c\
	     mathlib_config_msvc.h \
	     BCB_DPChange.c BCB_DPChange.h BCB_endian.h MSVC_endian.h \
	     MSVC_DPChange.h MSVC_DPChange.c 

lib_LTLIBRARIES = libultim.la

libultim_la_LDFLAGS = -version-info $(LT_VERSION_INFO) -release $(LT_RELEASE)

libultim_la_SOURCES = \
	atnat2.c    halfulp.c  mplog.c     slowexp2.c  ucot.c   upow.c  \
	atnat.c     mpa.c      mpsqrt.c    slowexp.c   uexp2.c  urem.c  \
	branred.c   mpatan2.c  mptan.c     slowlog2.c  uexp.c   uroot.c \
	doasin.c    mpatan.c   sincos32.c  slowpow.c   ulog2.c  usncs.c \
	dosincos.c  mpexp.c    slowcot.c   uasncs.c    ulog.c   utan.c  \
	DPChange.c

include_HEADERS = MathLib.h mathlib_configuration.h \
	mathlib_config.h

noinst_HEADERS = \
	atnat2.h   doasin.h    mpa.h     mpsqrt.h    uasncs.h  ulog.h   usncs.h \
	atnat.h    dosincos.h  mpatan.h  mydefs.h    ucot.h    upow.h   utan.h  \
	branred.h  mpexp.h   sincos32.h  uexp.h      urem.h    dla.h    mpa2.h  \
	mplog.h   trigo.h     ulog2.h   uroot.h	LINUX_DPChange.h SUN_DPChange.h \
	AIX_DPChange.h IX86MACOSX_DPChange.h \
	AIX_endian.h IX86_endian.h SUN_endian.h DPChange.h \
	endian.h BCB_endian.h

install-data-local:
	$(mkinstalldirs) "$(DESTDIR)/$(includedir)"
	$(INSTALL_DATA) $(srcdir)/MathLib.h "$(DESTDIR)/$(includedir)"
