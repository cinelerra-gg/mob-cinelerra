plugin_LTLIBRARIES = zoomblur.la
zoomblur_la_LDFLAGS = -module -shared -avoid-version
zoomblur_la_LIBADD =
zoomblur_la_SOURCES = zoomblur.C
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = picon_png.h 
EXTRA_DIST = picon.png
