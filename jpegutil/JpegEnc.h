#ifndef JPEGENC_H_
#define JPEGENC_H_

#include "JpegHandler.h"

namespace jpegutil
{

/**
 * JPEG encoder.
 */
class JpegEnc : public JpegHandler
{
public:
	JpegEnc();
	virtual ~JpegEnc();

	JpegEnc(const JpegEnc&);
	void operator=(const JpegEnc&);

	/**
	 * Encodes a raw image to a JPEG file on disk.
	 * @param[in] img      The raw image buffer.
	 * @param[in] width    A width of the image.
	 * @param[in] height   A height of the image.
	 * @param[in] fn       A file name.
	 * @return True if success or false if failed.
	 */
	bool encode(uint8_t* img, int width, int height, const char* fn);

	/**
	 * Sets a compression quality.
	 * @param quality The quality in percents [0, 100].
	 */
	void setQuality(int quality);

	/**
	 * Gets the current compression quality.
	 * @return The quality value.
	 */
	int getQuality() const;

private:
	jpeg_compress_struct comprInfo;
	int quality;
};

} // namespace jpegutil

#endif // JPEGENC_H_
