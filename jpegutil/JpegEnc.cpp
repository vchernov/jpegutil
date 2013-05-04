#include "JpegEnc.h"

namespace jpegutil
{

JpegEnc::JpegEnc()
{
	comprInfo.err = jpeg_std_error(&errMgr);
	jpeg_create_compress(&comprInfo);

	quality = 100;
}

JpegEnc::~JpegEnc()
{
	jpeg_destroy_compress(&comprInfo);
}

bool JpegEnc::encode(uint8_t* img, int width, int height, const char* fn)
{
	FILE* f = fopen(fn, "wb");
	if (!f)
		return false;

	jpeg_stdio_dest(&comprInfo, f);
	comprInfo.image_width = width;
	comprInfo.image_height = height;
	comprInfo.in_color_space = colorSpace;
	comprInfo.input_components = getNumComponents();
	jpeg_set_defaults(&comprInfo);
	jpeg_set_quality(&comprInfo, quality, true);

	jpeg_start_compress(&comprInfo, TRUE);
	int rowSize = comprInfo.image_width * comprInfo.input_components;
	JSAMPROW rows[1];
	while (comprInfo.next_scanline < comprInfo.image_height)
	{
		rows[0] = img + comprInfo.next_scanline * rowSize;
		jpeg_write_scanlines(&comprInfo, rows, 1);
	}

	jpeg_finish_compress(&comprInfo);
	fclose(f);
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
