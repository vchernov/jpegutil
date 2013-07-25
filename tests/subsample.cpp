#include <assert.h>
#include <stdio.h>
#include <iostream>

#include "../jpegutil/JpegDec.h"

int main(int argc, char** argv)
{
	using namespace jpegutil;

	char const* srcFn = (argc >= 2) ? argv[1] : NULL;
	char const* dstFn = (argc >= 3) ? argv[2] : NULL;

	if (srcFn == NULL)
	{
		std::cout << "no input file passed to " << argv[0] << std::endl;
		return 0;
	}

	uint8_t* img = NULL;
	int width = 0;
	int height = 0;

	FILE* srcFile = fopen(srcFn, "rb");
	assert(srcFile != NULL);

	JpegDec* dec = new JpegDec();
	assert(dec->decodeI420(srcFile, img, width, height));
	delete dec;

	fclose(srcFile);

	FILE* dstFile = fopen(dstFn, "wb");
	assert(dstFile != NULL);

	const size_t lumLen = width * height;
	const size_t chromWidth = width / 2;
	const size_t chromHeight = height / 2;
	const size_t chromLen = chromWidth * chromHeight;

	const size_t dstSize = lumLen + chromLen + chromLen;
	fwrite(img, 1, dstSize, dstFile);

	fclose(dstFile);

	delete[] img;

	return 0;
}
