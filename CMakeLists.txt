cmake_minimum_required(VERSION 3.2)
project(jpegutil)

option(JPEGUTIL_BUILD_TESTS "Build tests" OFF)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14")
endif()

find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})

add_library(jpegutil STATIC
    jpegutil/JpegDec.cpp
    jpegutil/JpegDec.h
    jpegutil/JpegEnc.cpp
    jpegutil/JpegEnc.h
    jpegutil/JpegDecPlanarYCbCr.cpp
    jpegutil/JpegDecPlanarYCbCr.h
    jpegutil/jpegutil.cpp
    jpegutil/jpegutil.h
)

target_link_libraries(jpegutil ${JPEG_LIBRARY})

install(DIRECTORY jpegutil DESTINATION include FILES_MATCHING PATTERN "*.h")
install(TARGETS jpegutil DESTINATION lib)

if (JPEGUTIL_BUILD_TESTS)
    add_executable(encoder tests/encoder.cpp)
    target_link_libraries(encoder jpegutil)

    add_executable(readwrite tests/readwrite.cpp)
    target_link_libraries(readwrite jpegutil)

    add_executable(subsample tests/subsample.cpp)
    target_link_libraries(subsample jpegutil)

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tests")
    find_package(MimeUtil)
    if (MIMEUTIL_FOUND)
        include_directories(${MIMEUTIL_INCLUDE_DIR})
        add_executable(mjpeg tests/mjpeg.cpp)
        target_link_libraries(mjpeg jpegutil ${MIMEUTIL_LIBRARY})
    endif()
endif()
