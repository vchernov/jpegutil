#include <assert.h>
#include <iostream>

#include <timeutil/Timestamp.h>

#include "../jpegutil/MimeInfo.h"
#include "../jpegutil/MimeParser.h"
#include "../jpegutil/JpegDec.h"

int main(int argc, char** argv)
{
	using namespace timeutil;
	using namespace jpegutil;

	if (argc < 2)
	{
		std::cout << "MJPEG test skipped, no file specified" << std::endl;
		return 0;
	}
	const char* fn = argv[1];
	std::cout << "MJPEG file: " << fn << std::endl;

	FILE* file = fopen(fn, "rb");
	assert(file != NULL);

	MimeInfo* info = new MimeInfo();
	MimeParser* parser = new MimeParser(info);
	JpegDec* dec = new JpegDec();

	fseek(file, 0, SEEK_SET);
	size_t num = 1;
	while (true)
	{
		uint8_t* img = NULL;
		int width, height;

		Timestamp start = Timestamp::now();
		if (!parser->readNext(file))
			break;
		if (parser->getContentType() == "image/jpeg")
			assert(dec->decode(parser->getContent(), parser->getContentLength(), img, width, height));
		Timestamp stop = Timestamp::now();

		delete[] img;

		std::cout << num;
		std::cout << " " << parser->getContentType();
		std::cout << " size: " << parser->getContentLength();
		std::cout << " time: " << (stop - start).toStr();
		std::cout << std::endl;

		num++;
	}

	// tests correctness of reading from buffer
	fseek(file, 0, SEEK_SET);
	const size_t bufferSize = 1024;
	char* buffer = new char[bufferSize];
	size_t cnt = 0;
	while (!feof(file))
	{
		size_t readLen = fread(buffer, 1, bufferSize, file);
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
					cnt++;

					delete[] img;
				}
			}
		}
	}
	delete[] buffer;
	std::cout << "count: " << cnt << std::endl;

	delete dec;
	delete parser;
	delete info;

	fclose(file);
	return 0;
}
