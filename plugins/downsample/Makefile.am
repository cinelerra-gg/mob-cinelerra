plugin_LTLIBRARIES = downsample.la
downsample_la_LDFLAGS = -avoid-version -module -shared 
downsample_la_LIBADD = 
downsample_la_SOURCES = downsample.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = picon_png.h 
EXTRA_DIST = picon.png
