cmake_minimum_required(VERSION 2.8)

project(jpegutil)

find_package(JPEG REQUIRED)

include_directories(${JPEG_INCLUDE_DIR})

add_library(jpegutil STATIC
    jpegutil/JpegDec.cpp
    jpegutil/JpegDec.h
    jpegutil/JpegDecPlanarYCbCr.cpp
    jpegutil/JpegDecPlanarYCbCr.h
    jpegutil/JpegEnc.cpp
    jpegutil/JpegEnc.h
    jpegutil/jpegutil.cpp
    jpegutil/jpegutil.h
    jpegutil/MimeInfo.cpp
    jpegutil/MimeInfo.h
    jpegutil/MimeParser.cpp
    jpegutil/MimeParser.h
    jpegutil/MimeWriter.cpp
    jpegutil/MimeWriter.h
)

target_link_libraries(jpegutil ${JPEG_LIBRARY})

install(DIRECTORY jpegutil
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
install(TARGETS jpegutil
    DESTINATION lib
)

enable_testing()

add_executable(test_readwrite tests/readwrite.cpp)
target_link_libraries(test_readwrite jpegutil)

add_test(ReadWrite test_readwrite)
