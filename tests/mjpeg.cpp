#include <assert.h>
#include <iostream>

#include "../jpegutil/MimeInfo.h"
#include "../jpegutil/MimeParser.h"

int main(int argc, char** argv)
{
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

	size_t cnt = 0;
	while (parser->readNext(file))
	{
		std::cout << "loaded: " << parser->getContentType();
		std::cout << " " << parser->getContentLength();
		std::cout << std::endl;
		cnt++;
	}
	std::cout << "amount: " << cnt << std::endl;

	delete parser;
	delete info;

	fclose(file);
	return 0;
}
