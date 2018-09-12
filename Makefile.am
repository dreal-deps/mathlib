EXTRA_DIST = descriptions2.txt msvc NT

SUBDIRS = src
DISTCLEANFILES = conftest conftest.c conftest.o

# Requires automake 1.4
AUTOMAKE_OPTIONS = 1.4

ACLOCAL_AMFLAGS = -I m4

# Rule to build tar-gzipped distribution package
$(PACKAGE)-$(VERSION).tar.gz: dist

