plugin_LTLIBRARIES = oilpainting.la
oilpainting_la_LDFLAGS = -avoid-version -module -shared 
oilpainting_la_LIBADD = 
oilpainting_la_SOURCES = oil.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = oil.h picon_png.h 
EXTRA_DIST = picon.png
