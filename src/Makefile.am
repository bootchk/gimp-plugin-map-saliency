## reduced version of gimp-plugin-template/src/Makefile.am
## then extended with OpenCV

bin_PROGRAMS = gimp-plugin-engine-saliency

bindir = $(GIMP_LIBDIR)/plug-ins

gimp_plugin_engine_saliency_SOURCES = \
	main.c		\
	render.c	\
	render.h	\
	adaptOpenCV.cpp \
	adaptOpenCV.hpp

AM_CPPFLAGS =\
	-I$(top_srcdir)		\
	@GIMP_CFLAGS@		\
	-I$(includedir)

##AM_LDFLAGS =\
##    -L/usr/local/lib -Wl,-Bstatic -lsaliency
    
## OPENCV_LIBS is optional
## order is important
## commands to gcc driver for static
LDADD = $(GIMP_LIBS) $(STATICLIBS) $(OPENCV_LIBS)

