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

	/**
	 * Decodes a JPEG image from a memory buffer.
	 *
	 * @param[in]  buffer  the pointer to the buffer with encoded image
	 * @param[in]  len     the size of the buffer
	 * @param[out] img     the decoded raw image. The memory is allocated inside the function.
	 * @param[out] width   the width of the decoded image
	 * @param[out] height  the height of the decoded image
	 * @return             true if success, false if failed
	 */
	bool decode(uint8_t* buffer, size_t len, uint8_t*& img, int& width, int& height);

	/**
	 * Reads and decodes a JPEG image through file descriptor.
	 *
	 * @param[in]  file    the file descriptor
	 * @param[out] img     the decoded raw image. The memory is allocated inside the function.
	 * @param[out] width   the width of the decoded image
	 * @param[out] height  the height of the decoded image
	 * @return             true if success, false if failed
	 */
	bool decode(FILE* file, uint8_t*& img, int& width, int& height);

	/**
	 * Reads and decodes a JPEG file on disk.
	 *
	 * @param[in]  path    the path to the file
	 * @param[out] img     the decoded raw image. The memory is allocated inside the function.
	 * @param[out] width   the width of the decoded image
	 * @param[out] height  the height of the decoded image
	 * @return             true if success, false if failed
	 */
	bool decode(const char* path, uint8_t*& img, int& width, int& height);

	bool decodeI420(FILE* f, uint8_t*& img, int& width, int& height);

private:
	JpegDec(const JpegDec&);
	void operator=(const JpegDec&);

	bool decode(uint8_t*& img, int& width, int& height);

	jpeg_decompress_struct decInfo;

	JSAMPLE* cache;
	size_t cacheSize;
};

} // namespace jpegutil

#endif // JPEGDEC_H_
