#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>

#include "../jpegutil/JpegDecPlanarYCbCr.h"
#include "../jpegutil/JpegEnc.h"
#include "../jpegutil/jpegutil.h"

using namespace jpegutil;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " output_file" << std::endl;
        return 0;
    }

    const char* testFileName = argv[1];

    const int origWidth = 256;
    const int origHeight = 512;
    const int numComponents = getNumComponents(JCS_YCbCr);

    const int buffLen = origWidth * origHeight * numComponents;
    uint8_t* img = new uint8_t[buffLen];
    for (int i = 0; i < buffLen; i++) {
        img[i] = (uint8_t)(rand() % 255);
    }

    auto encoder = std::make_unique<JpegEnc>();
    encoder->setColorSpace(JCS_YCbCr, numComponents);
    assert(encoder->encode(img, origWidth, origHeight, testFileName));

    delete[] img;

    img = nullptr;
    int width = 0;
    int height = 0;
    FILE* testFile = fopen(testFileName, "rb");

    auto decoder = std::make_unique<JpegDecPlanarYCbCr>();
    assert(decoder->decodeI420(testFile, img, width, height));
    assert(img != nullptr);
    assert(width == origWidth);
    assert(height == origHeight);

    fclose(testFile);
    delete[] img;

    return 0;
}
