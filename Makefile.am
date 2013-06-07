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
	
check_PROGRAMS = tests/readwrite tests/mjpeg
TESTS = $(check_PROGRAMS)

tests_readwrite_SOURCES = tests/readwrite.cpp
tests_readwrite_LDADD = libjpegutil.la -ljpeg

tests_mjpeg_SOURCES = tests/mjpeg.cpp
tests_mjpeg_LDADD = libjpegutil.la -ljpeg -ltimeutil
