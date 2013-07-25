#ifndef JPEGDECPLANARYCBCR_H_
#define JPEGDECPLANARYCBCR_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <jpeglib.h>

namespace jpegutil
{

class JpegDecPlanarYCbCr
{
public:
	JpegDecPlanarYCbCr();
	virtual ~JpegDecPlanarYCbCr();

	bool decodeI420(FILE* file, uint8_t*& img, int& width, int& height);

private:
	JpegDecPlanarYCbCr(const JpegDecPlanarYCbCr&);
	void operator=(const JpegDecPlanarYCbCr&);

	jpeg_decompress_struct decInfo;
	jpeg_error_mgr errMgr;

	JSAMPLE* cache;
	size_t cacheSize;
};

} // namespace jpegutil

#endif // JPEGDECPLANARYCBCR_H_
