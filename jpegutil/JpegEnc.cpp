#include "JpegEnc.h"

namespace jpegutil {

JpegEnc::JpegEnc() {
    encInfo.err = jpeg_std_error(&errMgr);
    jpeg_create_compress(&encInfo);
}

JpegEnc::~JpegEnc() {
    jpeg_destroy_compress(&encInfo);
}

void JpegEnc::setColorSpace(J_COLOR_SPACE colorSpace, int numComponents) {
    this->colorSpace = colorSpace;
    this->numComponents = numComponents;
}

J_COLOR_SPACE JpegEnc::getColorSpace() const {
    return colorSpace;
}

int JpegEnc::getNumComponents() const {
    return numComponents;
}

void JpegEnc::setQuality(int quality) {
    this->quality = quality;
}

int JpegEnc::getQuality() const {
    return quality;
}

bool JpegEnc::encode(uint8_t* img, int width, int height, FILE* file) {
    if (file == nullptr) {
        return false;
    }

    jpeg_stdio_dest(&encInfo, file);
    return encode(img, width, height);
}

bool JpegEnc::encode(uint8_t* img, int width, int height, const char* path) {
    FILE* file = fopen(path, "wb");
    bool rv = encode(img, width, height, file);
    fclose(file);
    return rv;
}

bool JpegEnc::encode(uint8_t* img, int width, int height) {
    encInfo.image_width = width;
    encInfo.image_height = height;
    encInfo.in_color_space = colorSpace;
    encInfo.input_components = numComponents;
    jpeg_set_defaults(&encInfo);
    jpeg_set_quality(&encInfo, quality, true);

    jpeg_start_compress(&encInfo, true);

    int rowSize = encInfo.image_width * encInfo.input_components;
    JSAMPROW rows[1];
    while (encInfo.next_scanline < encInfo.image_height) {
        rows[0] = img + encInfo.next_scanline * rowSize;
        jpeg_write_scanlines(&encInfo, rows, 1);
    }

    jpeg_finish_compress(&encInfo);
    return true;
}

}
