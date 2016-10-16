#include <assert.h>
#include <iostream>
#include <chrono>

#include "../jpegutil/MimeInfo.h"
#include "../jpegutil/MimeParser.h"
#include "../jpegutil/MimeWriter.h"
#include "../jpegutil/JpegDec.h"

int main(int argc, char** argv) {
    using namespace jpegutil;

    if (argc < 2) {
        std::cout << "No file specified, MJPEG test skipped" << std::endl;
        return 0;
    }

    const char* testFileName = argv[1];
    const char* copyFileName = "copy.mjpeg";
    std::cout << "MJPEG file: " << testFileName << std::endl;

    MimeInfo* info = new MimeInfo();
    MimeParser* parser = new MimeParser(info);
    MimeWriter* writer = new MimeWriter(info);
    JpegDec* dec = new JpegDec();

    FILE* inFile = fopen(testFileName, "rb");
    assert(inFile != nullptr);

    FILE* outFile = fopen(copyFileName, "wb");
    assert(outFile != nullptr);

    size_t origCount = 0;
    size_t num = 1;
    while (true) {
        uint8_t* img = nullptr;
        int width, height;

        auto start = std::chrono::steady_clock::now();
        if (!parser->readNext(inFile)) {
            break;
        }
        if (parser->getContentType() == "image/jpeg") {
            assert(dec->decode(parser->getContent(), parser->getContentLength(), img, width, height));
            origCount++;
        }
        auto end = std::chrono::steady_clock::now();

        delete[] img;

        writer->write(parser->getContent(), parser->getContentLength(), parser->getContentType(), outFile);

        std::cout << num;
        std::cout << " " << parser->getContentType();
        std::cout << " size: " << parser->getContentLength();
        std::cout << " time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms";
        std::cout << std::endl;

        num++;
    }

    fclose(outFile);
    fclose(inFile);

    FILE* testFile = fopen(copyFileName, "rb");
    assert(testFile != nullptr);

    // tests correctness of reading from buffer
    const size_t bufferSize = 4096;
    char* buffer = new char[bufferSize];
    size_t copyCount = 0;
    while (!feof(testFile)) {
        size_t readLen = fread(buffer, 1, bufferSize, testFile);
        size_t offset = 0;
        while (offset < readLen) {
            if (parser->readNext(buffer, readLen, offset)) {
                if (parser->getContentType() == "image/jpeg") {
                    uint8_t* img = nullptr;
                    int width, height;

                    assert(dec->decode(parser->getContent(), parser->getContentLength(), img, width, height));
                    copyCount++;

                    delete[] img;
                }
            }
        }
    }
    delete[] buffer;

    fclose(testFile);

    assert(copyCount == origCount);
    std::cout << "MJPEG test complete" << std::endl;

    delete dec;
    delete parser;
    delete writer;
    delete info;
    return 0;
}
