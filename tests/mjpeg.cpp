#include <assert.h>
#include <iostream>

#include <timeutil/Timestamp.h>

#include "../jpegutil/MimeInfo.h"
#include "../jpegutil/MimeParser.h"

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

	size_t num = 1;
	while (true)
	{
		Timestamp start = Timestamp::now();
		if (!parser->readNext(file))
			break;
		Timestamp stop = Timestamp::now();

		std::cout << num;
		std::cout << " " << parser->getContentType();
		std::cout << " size: " << parser->getContentLength();
		std::cout << " time: " << (stop - start).toStr();
		std::cout << std::endl;

		num++;
	}

	delete parser;
	delete info;

	fclose(file);
	return 0;
}
