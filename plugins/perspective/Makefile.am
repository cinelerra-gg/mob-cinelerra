plugin_LTLIBRARIES = perspective.la
perspective_la_LDFLAGS = -avoid-version -module -shared 
perspective_la_LIBADD = $(top_builddir)/plugins/motion/libaffine.la
perspective_la_SOURCES = perspective.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = perspective.h picon_png.h 
EXTRA_DIST = picon.png
