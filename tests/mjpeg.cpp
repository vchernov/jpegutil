#include <assert.h>
#include <iostream>

#include "../jpegutil/MimeReader.h"
#include "../jpegutil/MimeWriter.h"

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

	return 0;
}
