#ifndef JPEGDECPLANARYCBCR_H_
#define JPEGDECPLANARYCBCR_H_

#include <cstdlib>
#include <cstdio>
#include <cstdint>

#include <jpeglib.h>

namespace jpegutil {

class JpegDecPlanarYCbCr {
public:
    JpegDecPlanarYCbCr();
    virtual ~JpegDecPlanarYCbCr();

    JpegDecPlanarYCbCr(const JpegDecPlanarYCbCr&) = delete;
    void operator=(const JpegDecPlanarYCbCr&) = delete;

    bool decodeI420(FILE* file, uint8_t*& img, int& width, int& height);

private:
    jpeg_decompress_struct decInfo;
    jpeg_error_mgr errMgr;

    JSAMPLE* cache = nullptr;
    size_t cacheSize = 0;
};

}

#endif // JPEGDECPLANARYCBCR_H_
