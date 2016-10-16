cmake_minimum_required(VERSION 2.8)

project(jpegutil)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
endif()

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

add_executable(readwrite tests/readwrite.cpp)
target_link_libraries(readwrite jpegutil)
add_test(ReadWrite readwrite)

add_executable(mjpeg tests/mjpeg.cpp)
target_link_libraries(mjpeg jpegutil)
add_test(MJPEG mjpeg)

add_executable(subsample tests/subsample.cpp)
target_link_libraries(subsample jpegutil)
add_test(Subsample subsample)
