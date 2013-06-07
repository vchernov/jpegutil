#include <assert.h>
#include <iostream>

#include <timeutil/Timestamp.h>

#include "../jpegutil/MimeInfo.h"
#include "../jpegutil/MimeParser.h"
#include "../jpegutil/MimeWriter.h"
#include "../jpegutil/JpegDec.h"

int main(int argc, char** argv)
{
	using namespace jpegutil;
	using namespace timeutil;

	if (argc < 2)
	{
		std::cout << "MJPEG test skipped, no file specified" << std::endl;
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
	assert(inFile != NULL);

	FILE* outFile = fopen(copyFileName, "wb");
	assert(outFile != NULL);

	size_t origCount = 0;
	size_t num = 1;
	while (true)
	{
		uint8_t* img = NULL;
		int width, height;

		Timestamp start = Timestamp::now();
		if (!parser->readNext(inFile))
			break;
		if (parser->getContentType() == "image/jpeg")
		{
			assert(dec->decode(parser->getContent(), parser->getContentLength(), img, width, height));
			origCount++;
		}
		Timestamp stop = Timestamp::now();

		delete[] img;

		writer->write(parser->getContent(), parser->getContentLength(), parser->getContentType(), outFile);

		std::cout << num;
		std::cout << " " << parser->getContentType();
		std::cout << " size: " << parser->getContentLength();
		std::cout << " time: " << (stop - start).toStr();
		std::cout << std::endl;

		num++;
	}

	fclose(outFile);
	fclose(inFile);

	FILE* testFile = fopen(copyFileName, "rb");
	assert(testFile != NULL);

	// tests correctness of reading from buffer
	const size_t bufferSize = 4096;
	char* buffer = new char[bufferSize];
	size_t copyCount = 0;
	while (!feof(testFile))
	{
		size_t readLen = fread(buffer, 1, bufferSize, testFile);
		size_t offset = 0;
		while (offset < readLen)
		{
			if (parser->readNext(buffer, readLen, offset))
			{
				if (parser->getContentType() == "image/jpeg")
				{
					uint8_t* img = NULL;
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
