ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST = m4/NOTES

lib_LTLIBRARIES = libjpegutil.la

libjpegutil_la_SOURCES = \
	jpegutil/JpegHandler.h \
	jpegutil/JpegHandler.cpp \
	jpegutil/JpegDec.h \
	jpegutil/JpegDec.cpp \
	jpegutil/JpegEnc.h \
	jpegutil/JpegEnc.cpp

nobase_include_HEADERS = \
	jpegutil/JpegHandler.h \
	jpegutil/JpegDec.h \
	jpegutil/JpegEnc.h

check_PROGRAMS = tests/readwrite
TESTS = $(check_PROGRAMS)

tests_readwrite_SOURCES = tests/readwrite.cpp
tests_readwrite_LDADD = libjpegutil.la -ljpeg
