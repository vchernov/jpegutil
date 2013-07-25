#include <assert.h>
#include <iostream>

#include "../jpegutil/jpegutil.h"

int main(int, char**)
{
	using namespace jpegutil;

	const char* fn = "test.jpeg";
	const int imgWidth = 512;
	const int imgHeight = 256;

	const int buffLen = imgWidth * imgHeight * 3;
	uint8_t* img = new uint8_t[buffLen];
	for (int i = 0; i < buffLen; i++)
		img[i] = rand() % 255;

	JpegEnc* enc = new JpegEnc();
	enc->setColorSpace(JCS_RGB, 3);
	assert(enc->encode(img, imgWidth, imgHeight, fn));
	delete enc;

	delete[] img;
	img = NULL;

	JpegDec* dec = new JpegDec();
	dec->setColorSpace(JCS_YCbCr);

	int width = 0;
	int height = 0;
	assert(dec->decode(fn, img, width, height));
	assert(img != NULL);
	assert(width == imgWidth);
	assert(height == imgHeight);

	delete[] img;

	return 0;
}
