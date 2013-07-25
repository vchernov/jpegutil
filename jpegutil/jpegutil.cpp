#include "jpegutil.h"

namespace jpegutil
{

int getNumComponents(J_COLOR_SPACE colorSpace)
{
	switch (colorSpace)
	{
	case JCS_GRAYSCALE:
		return 1;
	case JCS_RGB:
	case JCS_YCbCr:
		return 3;
	case JCS_CMYK:
		return 4;
	default:
		return 0;
	}
}

} // namespace jpegutil
