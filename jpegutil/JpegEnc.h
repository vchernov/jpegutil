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

	/**
	 * Encodes a raw image to a JPEG file on disk using file descriptor.
	 *
	 * @param img     the pointer to buffer with the raw image
	 * @param width   the width of the image
	 * @param height  the height of the image
	 * @param file    the file descriptor
	 * @return        true if success, false if failed
	 */
	bool encode(uint8_t* img, int width, int height, FILE* file);

	/**
	 * Encodes a raw image to a JPEG file on disk using path.
	 *
	 * @param img     the pointer to buffer with the raw image
	 * @param width   the width of the image
	 * @param height  the height of the image
	 * @param path    the path to the file
	 * @return        true if success, false if failed
	 */
	bool encode(uint8_t* img, int width, int height, const char* path);

	/**
	 * Sets a compression quality.
	 *
	 * @param quality  the quality in percents [0, 100]
	 */
	void setQuality(int quality);

	/**
	 * Gets the current compression quality.
	 *
	 * @return  the quality value
	 */
	int getQuality() const;

private:
	JpegEnc(const JpegEnc&);
	void operator=(const JpegEnc&);

	bool encode(uint8_t* img, int width, int height);

	jpeg_compress_struct encInfo;
	int quality;
};

} // namespace jpegutil

#endif // JPEGENC_H_
