plugin_LTLIBRARIES = resample.la
resample_la_LDFLAGS = -avoid-version -module -shared 
resample_la_LIBADD = 
resample_la_SOURCES = resample.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = picon_png.h resample.h 
EXTRA_DIST = picon.png
