plugin_LTLIBRARIES = denoise.la
denoise_la_LDFLAGS = -avoid-version -module -shared 
denoise_la_LIBADD = 
denoise_la_SOURCES = denoise.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

AM_CPPFLAGS = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = denoise.h picon_png.h 
EXTRA_DIST = picon.png
