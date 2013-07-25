ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST = m4/NOTES

lib_LTLIBRARIES = libjpegutil.la

libjpegutil_la_SOURCES = \
	jpegutil/JpegHandler.h \
	jpegutil/JpegHandler.cpp \
	jpegutil/JpegDec.h \
	jpegutil/JpegDec.cpp \
	jpegutil/JpegEnc.h \
	jpegutil/JpegEnc.cpp \
	jpegutil/MimeInfo.h \
	jpegutil/MimeInfo.cpp \
	jpegutil/MimeParser.h \
	jpegutil/MimeParser.cpp \
	jpegutil/MimeWriter.h \
	jpegutil/MimeWriter.cpp

nobase_include_HEADERS = \
	jpegutil/JpegHandler.h \
	jpegutil/JpegDec.h \
	jpegutil/JpegEnc.h \
	jpegutil/MimeInfo.h \
	jpegutil/MimeParser.h \
	jpegutil/MimeWriter.h

libjpegutil_la_LDFLAGS = -no-undefined \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

TESTS = tests/readwrite tests/subsample tests/mjpeg
check_PROGRAMS = $(TESTS)

tests_readwrite_SOURCES = tests/readwrite.cpp
tests_readwrite_LDADD = libjpegutil.la -ljpeg

tests_subsample_SOURCES = tests/subsample.cpp
tests_subsample_LDADD = libjpegutil.la -ljpeg

tests_mjpeg_SOURCES = tests/mjpeg.cpp
tests_mjpeg_LDADD = libjpegutil.la -ljpeg -ltimeutil

.PHONY: check-norun
check-norun: $(check_PROGRAMS)
