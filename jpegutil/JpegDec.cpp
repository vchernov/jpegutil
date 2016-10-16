#include "JpegDec.h"

namespace jpegutil {

JpegDec::JpegDec() {
    decInfo.err = jpeg_std_error(&errMgr);
    jpeg_create_decompress(&decInfo);
}

JpegDec::~JpegDec() {
    jpeg_destroy_decompress(&decInfo);
}

void JpegDec::setColorSpace(J_COLOR_SPACE colorSpace) {
    this->colorSpace = colorSpace;
}

J_COLOR_SPACE JpegDec::getColorSpace() const {
    return colorSpace;
}

bool JpegDec::decode(uint8_t* buffer, size_t len, uint8_t*& img, int& width, int& height) {
    if (buffer == nullptr) {
        return false;
    }

    jpeg_mem_src(&decInfo, buffer, len);
    return decode(img, width, height);
}

bool JpegDec::decode(FILE* file, uint8_t*& img, int& width, int& height) {
    if (file == nullptr) {
        return false;
    }

    jpeg_stdio_src(&decInfo, file);
    return decode(img, width, height);
}

bool JpegDec::decode(const char* path, uint8_t*& img, int& width, int& height) {
    FILE* file = fopen(path, "rb");
    bool rv = decode(file, img, width, height);
    fclose(file);
    return rv;
}

bool JpegDec::decode(uint8_t*& img, int& width, int& height) {
    jpeg_read_header(&decInfo, true);
    decInfo.out_color_space = colorSpace;
    decInfo.raw_data_out = false;

    jpeg_start_decompress(&decInfo);

    width = decInfo.image_width;
    height = decInfo.image_height;
    size_t rowSize = decInfo.image_width * decInfo.num_components;
    img = new uint8_t[decInfo.image_height * rowSize];

    JSAMPROW rows[1];
    size_t offset = 0;
    while (decInfo.output_scanline < decInfo.image_height) {
        rows[0] = img + offset;
        jpeg_read_scanlines(&decInfo, rows, 1);
        offset += rowSize;
    }

    jpeg_finish_decompress(&decInfo);
    return true;
}

}
