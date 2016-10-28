#ifndef JPEGUTIL_H_
#define JPEGUTIL_H_

#include <cstdlib>
#include <cstdio>

#include <jpeglib.h>

namespace jpegutil {

/**
 * Gets a number of color components for the given color space.
 *
 * @param colorSpace  the color space
 * @return            the number of components for supported color space; 0 for unsupported
 */
int getNumComponents(J_COLOR_SPACE colorSpace);

}

#endif // JPEGUTIL_H_
