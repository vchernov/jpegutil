#include <cassert>
#include <chrono>
#include <iostream>

#include <mimeutil/MimeParser.h>

#include "../jpegutil/JpegDec.h"

using namespace jpegutil;
using namespace mimeutil;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " MJPEG_file" << std::endl;
        return 0;
    }

    const char* testFileName = argv[1];
    FILE* testFile = fopen(testFileName, "rb");
    assert(testFile != nullptr);

    auto parser = std::make_unique<MimeParser>();
    auto decoder = std::make_unique<JpegDec>();

    size_t frameNum = 0;
    while (true) {
        uint8_t* img = nullptr;
        int width, height;

        auto start = std::chrono::steady_clock::now();

        if (!parser->readNext(testFile)) {
            break;
        }
        frameNum++;

        if (parser->getContentType() == "image/jpeg") {
            assert(decoder->decode(parser->getContent(), parser->getContentLength(), img, width, height));
        }

        auto end = std::chrono::steady_clock::now();

        std::cout << "frame #" << frameNum;
        std::cout << " size: " << parser->getContentLength();
        std::cout << " time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms";
        std::cout << std::endl;

        delete[] img;
    }
    return 0;
}
