#ifndef JPEGENC_H_
#define JPEGENC_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <jpeglib.h>

namespace jpegutil
{

/**
 * JPEG encoder.
 *
 * The color space by default is RGB.
 */
class JpegEnc
{
public:
	JpegEnc();
	virtual ~JpegEnc();

	/**
	 * Sets the color space of the images to be worked with.
	 *
	 * @param colorSpace     the color space. Can be: JCS_GRAYSCALE, JCS_RGB, JCS_YCbCr, or JCS_CMYK.
	 * @param numComponents  the number of components in the color space specified
	 */
	void setColorSpace(J_COLOR_SPACE colorSpace, int numComponents);

	/**
	 * Gets the current color space.
	 *
	 * @return  the color space identificator
	 */
	J_COLOR_SPACE getColorSpace() const;

	/**
	 * Gets the number of components in the current color space.
	 *
	 * @return  the number of color space components
	 */
	int getNumComponents() const;

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

private:
	JpegEnc(const JpegEnc&);
	void operator=(const JpegEnc&);

	bool encode(uint8_t* img, int width, int height);

	jpeg_compress_struct encInfo;
	jpeg_error_mgr errMgr;

	J_COLOR_SPACE colorSpace;
	int numComponents;

	int quality;
};

} // namespace jpegutil

#endif // JPEGENC_H_
