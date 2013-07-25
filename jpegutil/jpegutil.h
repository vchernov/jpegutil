#ifndef JPEGUTIL_H_
#define JPEGUTIL_H_

#include <stdlib.h>
#include <stdio.h>

#include <jpeglib.h>

#include "JpegDec.h"
#include "JpegEnc.h"
#include "JpegDecPlanarYCbCr.h"

namespace jpegutil
{

/**
 * Gets a number of color components for the given color space.
 *
 * @param colorSpace  the color space
 * @return            the number of components for supported color space; 0 for unsupported
 */
int getNumComponents(J_COLOR_SPACE colorSpace);

} // namespace jpegutil

#endif // JPEGUTIL_H_
