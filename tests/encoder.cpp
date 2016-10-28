#include <cassert>
#include <iostream>
#include <bits/unique_ptr.h>

#include "../jpegutil/JpegEnc.h"

using namespace jpegutil;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " output_file" << std::endl;
        return 0;
    }

    const char* outFileName = argv[1];

    int width = 256;
    int height = 256;
    uint8_t* img = new uint8_t[width * height * 3];
    for (int y = 0; y < height; y++) {
        int row = width * y * 3;
        for (int x = 0; x < width; x++) {
            int offset = row + x * 3;
            img[offset] = (uint8_t)x;
            img[offset + 1] = (uint8_t)y;
            img[offset + 2] = 0;
        }
    }

    auto encoder = std::make_unique<JpegEnc>();
    encoder->setColorSpace(JCS_RGB, 3);
    assert(encoder->encode(img, width, height, outFileName));

    delete[] img;
    return 0;
}
