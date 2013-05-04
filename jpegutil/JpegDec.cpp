#include "JpegDec.h"

#include <string.h>

namespace jpegutil
{

JpegDec::JpegDec()
{
	decInfo.err = jpeg_std_error(&errMgr);
	jpeg_create_decompress(&decInfo);

	row = NULL;
	rowSize = 0;
}

JpegDec::~JpegDec()
{
	jpeg_destroy_decompress(&decInfo);
	delete[] row;
}

bool JpegDec::decode(uint8_t*& img, int& width, int& height)
{
	jpeg_read_header(&decInfo, TRUE);
	decInfo.out_color_space = colorSpace;

	jpeg_start_decompress(&decInfo);
	size_t newRowSize = decInfo.image_width * decInfo.num_components;
	if (newRowSize != rowSize)
	{
		delete[] row;
		row = new JSAMPLE[newRowSize];
		rowSize = newRowSize;
	}

	width = decInfo.image_width;
	height = decInfo.image_height;
	img = new uint8_t[decInfo.image_height * rowSize];

	JSAMPROW rows[1] = { row };
	size_t offset = 0;
	while (decInfo.output_scanline < decInfo.image_height)
	{
		jpeg_read_scanlines(&decInfo, rows, 1);
		memcpy(img + offset, row, rowSize);
		offset += rowSize;
	}

	jpeg_finish_decompress(&decInfo);
	return true;
}

bool JpegDec::decode(const char* fn, uint8_t*& img, int& width, int& height)
{
	FILE* f = fopen(fn, "rb");
	if (!f)
		return false;

	jpeg_stdio_src(&decInfo, f);
	bool rv = decode(img, width, height);
	fclose(f);
	return rv;
}

bool JpegDec::decode(uint8_t* buffer, size_t len, uint8_t*& img, int& width, int& height)
{
	if (!buffer)
		return false;

	jpeg_mem_src(&decInfo, buffer, len);
	return decode(img, width, height);
}

} // namespace jpegutil
