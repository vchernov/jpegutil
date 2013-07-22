#include "JpegDec.h"

#include <string.h>

namespace jpegutil
{

JpegDec::JpegDec()
{
	decInfo.err = jpeg_std_error(&errMgr);
	jpeg_create_decompress(&decInfo);

	cache = NULL;
	cacheSize = 0;
}

JpegDec::~JpegDec()
{
	jpeg_destroy_decompress(&decInfo);
	delete[] cache;
}

bool JpegDec::decode(uint8_t*& img, int& width, int& height)
{
	jpeg_read_header(&decInfo, TRUE);
	decInfo.out_color_space = colorSpace;
	decInfo.raw_data_out = FALSE;

	jpeg_start_decompress(&decInfo);
	size_t newCacheSize = decInfo.image_width * decInfo.num_components;
	if (newCacheSize != cacheSize)
	{
		delete[] cache;
		cache = new JSAMPLE[newCacheSize];
		cacheSize = newCacheSize;
	}

	width = decInfo.image_width;
	height = decInfo.image_height;
	img = new uint8_t[decInfo.image_height * cacheSize];

	JSAMPROW rows[1] = { cache };
	size_t offset = 0;
	while (decInfo.output_scanline < decInfo.image_height)
	{
		jpeg_read_scanlines(&decInfo, rows, 1);
		memcpy(img + offset, cache, cacheSize);
		offset += cacheSize;
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

bool JpegDec::decodeI420(FILE* f, uint8_t*& img, int& width, int& height)
{
	jpeg_stdio_src(&decInfo, f);

	jpeg_read_header(&decInfo, TRUE);
	decInfo.out_color_space = JCS_YCbCr;
	decInfo.raw_data_out = TRUE;

	jpeg_start_decompress(&decInfo);

	const size_t linesCount = decInfo.max_v_samp_factor * DCTSIZE;

	size_t newCacheSize = linesCount * decInfo.output_width * decInfo.out_color_components;
	if (newCacheSize != cacheSize)
	{
		delete[] cache;
		cache = new JSAMPLE[newCacheSize];
		cacheSize = newCacheSize;
	}

	JSAMPROW cols[3][linesCount];
	JSAMPLE* ptr = cache;
	for (int c = 0; c < 3; c++)
	{
		for (size_t i = 0; i < linesCount; i++)
		{
			cols[c][i] = ptr;
			ptr += decInfo.output_width;
		}
	}

	JSAMPARRAY yuvPtr[3] = { cols[0], cols[1], cols[2] };

	const size_t lumLen = decInfo.output_width * decInfo.output_height;
	const size_t chromWidth = decInfo.output_width / 2;
	const size_t chromHeight = decInfo.output_height / 2;
	const size_t chromLen = chromWidth * chromHeight;
	const size_t dstSize = lumLen + chromLen + chromLen;
	JSAMPLE* dst = new JSAMPLE[dstSize];

	JSAMPLE * y = dst;
	JSAMPLE * u = y + lumLen;
	JSAMPLE * v = u + chromLen;

	for (size_t row = 0; row < decInfo.output_height; row += linesCount)
	{
		jpeg_read_raw_data(&decInfo, yuvPtr, linesCount);

		// 4:4:4 -> I420

		for (size_t i = 0; i < linesCount; i++)
		{
			memcpy(y, cols[0][i], decInfo.output_width);
			y += decInfo.output_width;
		}

		for (size_t i = 0; i < linesCount; i += 2)
		{
			for (size_t j = 0; j != decInfo.output_width; j += 2)
			{
				*u = cols[1][i][j];
				u += 1;

				*v = cols[2][i][j];
				v += 1;
			}
		}
	}

	img = dst;
	width = decInfo.output_width;
	height = decInfo.output_height;

	jpeg_finish_decompress(&decInfo);
	return true;
}

} // namespace jpegutil
