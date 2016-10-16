#include <assert.h>
#include <stdio.h>
#include <iostream>

#include "../jpegutil/JpegDecPlanarYCbCr.h"

int main(int argc, char** argv) {
    using namespace jpegutil;

    char const* srcFn = (argc >= 2) ? argv[1] : nullptr;
    char const* dstFn = (argc >= 3) ? argv[2] : nullptr;

    uint8_t* img = nullptr;
    int width = 0;
    int height = 0;

    if (srcFn != nullptr) {
        FILE* srcFile = fopen(srcFn, "rb");
        assert(srcFile != NULL);

        JpegDecPlanarYCbCr* dec = new JpegDecPlanarYCbCr();
        assert(dec->decodeI420(srcFile, img, width, height));
        delete dec;

        fclose(srcFile);
    } else {
        std::cout << "No input file passed to " << argv[0] << std::endl;
        return 0;
    }

    if (dstFn != nullptr) {
        FILE* dstFile = fopen(dstFn, "wb");
        assert(dstFile != nullptr);

        const int lumLen = width * height;
        const int chromWidth = width / 2;
        const int chromHeight = height / 2;
        const int chromLen = chromWidth * chromHeight;

        const size_t dstSize = lumLen + chromLen + chromLen;
        fwrite(img, 1, dstSize, dstFile);

        fclose(dstFile);
    }

    delete[] img;

    return 0;
}
