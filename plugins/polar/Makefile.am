plugin_LTLIBRARIES = polar.la
polar_la_LDFLAGS = -avoid-version -module -shared 
polar_la_LIBADD = 
polar_la_SOURCES = polar.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = picon_png.h polar.h
EXTRA_DIST = picon.png
