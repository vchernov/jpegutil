#include "JpegEnc.h"

namespace jpegutil
{

JpegEnc::JpegEnc()
{
	encInfo.err = jpeg_std_error(&errMgr);
	jpeg_create_compress(&encInfo);

	quality = 80;
}

JpegEnc::~JpegEnc()
{
	jpeg_destroy_compress(&encInfo);
}

bool JpegEnc::encode(uint8_t* img, int width, int height, FILE* file)
{
	if (file == NULL)
		return false;

	jpeg_stdio_dest(&encInfo, file);
	return encode(img, width, height);
}

bool JpegEnc::encode(uint8_t* img, int width, int height, const char* path)
{
	FILE* file = fopen(path, "wb");
	bool rv = encode(img, width, height, file);
	fclose(file);
	return rv;
}

bool JpegEnc::encode(uint8_t* img, int width, int height)
{
	encInfo.image_width = width;
	encInfo.image_height = height;
	encInfo.in_color_space = colorSpace;
	encInfo.input_components = getNumComponents();
	jpeg_set_defaults(&encInfo);
	jpeg_set_quality(&encInfo, quality, TRUE);

	jpeg_start_compress(&encInfo, TRUE);

	int rowSize = encInfo.image_width * encInfo.input_components;
	JSAMPROW rows[1];
	while (encInfo.next_scanline < encInfo.image_height)
	{
		rows[0] = img + encInfo.next_scanline * rowSize;
		jpeg_write_scanlines(&encInfo, rows, 1);
	}

	jpeg_finish_compress(&encInfo);
	return true;
}

void JpegEnc::setQuality(int quality)
{
	this->quality = quality;
}

int JpegEnc::getQuality() const
{
	return quality;
}

} // namespace jpegutil
