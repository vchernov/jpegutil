#ifndef JPEGHANDLER_H_
#define JPEGHANDLER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <jpeglib.h>

namespace jpegutil
{

/**
 * Base class for JPEG decoder and encoder.
 *
 * Encapsulates common features of JpegDec and JpegEnc.
 * The default color space is JCS_RGB.
 */
class JpegHandler
{
public:
	JpegHandler();
	virtual ~JpegHandler();

	/**
	 * Sets the color space of the images to be worked with.
	 * @param[in] colorSpace The color space. Can be: JCS_GRAYSCALE, JCS_RGB, JCS_YCbCr, or JCS_CMYK.
	 */
	void setColorSpace(J_COLOR_SPACE colorSpace);

	/**
	 * Gets the current color space.
	 * @return The color space value.
	 */
	J_COLOR_SPACE getColorSpace() const;

	/**
	 * Gets a number of color components according to the current color space.
	 * @return The number of components for supported color spaces, or 0 for unsupported.
	 */
	int getNumComponents() const;

protected:
	jpeg_error_mgr errMgr;
	J_COLOR_SPACE colorSpace;
};

} // namespace jpegutil

#endif // JPEGHANDLER_H_
