#ifndef JPEGDEC_H_
#define JPEGDEC_H_

#include "JpegHandler.h"

namespace jpegutil
{

/**
 * JPEG decoder.
 */
class JpegDec: public JpegHandler
{
public:
	JpegDec();
	virtual ~JpegDec();

	JpegDec(const JpegDec&);
	void operator=(const JpegDec&);

	/**
	 * Reads and decodes a JPEG file on disk.
	 * @param[in]  fn      A file name.
	 * @param[out] img     The decoded raw image. The memory is allocated inside the function.
	 * @param[out] width   A width of the decoded image.
	 * @param[out] height  A height of the decoded image.
	 * @return True if success or false if failed.
	 */
	bool decode(const char* fn, uint8_t*& img, int& width, int& height);

	/**
	 * Decodes a JPEG image from a memory buffer.
	 * @param[in]  buffer  A pointer to the buffer with encoded image.
	 * @param[in]  len     A size of the buffer.
	 * @param[out] img     The decoded raw image. The memory is allocated inside the function.
	 * @param[out] width   A width of the decoded image.
	 * @param[out] height  A height of the decoded image.
	 * @return True if success or false if failed.
	 */
	bool decode(uint8_t* buffer, size_t len, uint8_t*& img, int& width, int& height);

private:
	jpeg_decompress_struct decInfo;

	JSAMPROW row;
	size_t rowSize;

	bool decode(uint8_t*& img, int& width, int& height);
};

} // namespace jpegutil

#endif // JPEGDEC_H_
