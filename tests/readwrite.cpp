#include <cassert>
#include <iostream>

#include "../jpegutil/JpegDec.h"
#include "../jpegutil/JpegEnc.h"

using namespace jpegutil;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " output_file" << std::endl;
        return 0;
    }

    const char* testFileName = argv[1];

    const int imgWidth = 512;
    const int imgHeight = 256;

    const int buffLen = imgWidth * imgHeight * 3;
    uint8_t* img = new uint8_t[buffLen];
    for (int i = 0; i < buffLen; i++) {
        img[i] = (uint8_t)(rand() % 255);
    }

    JpegEnc* enc = new JpegEnc();
    enc->setColorSpace(JCS_RGB, 3);
    assert(enc->encode(img, imgWidth, imgHeight, testFileName));
    delete enc;

    delete[] img;
    img = nullptr;

    JpegDec* dec = new JpegDec();
    dec->setColorSpace(JCS_YCbCr);
    int width = 0;
    int height = 0;
    assert(dec->decode(testFileName, img, width, height));
    assert(img != nullptr);
    assert(width == imgWidth);
    assert(height == imgHeight);
    delete dec;

    delete[] img;

    return 0;
}
