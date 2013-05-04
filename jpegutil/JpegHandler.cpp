#include "JpegHandler.h"

namespace jpegutil
{

JpegHandler::JpegHandler()
{
	colorSpace = JCS_RGB;
}

JpegHandler::~JpegHandler()
{
}

void JpegHandler::setColorSpace(J_COLOR_SPACE colorSpace)
{
	this->colorSpace = colorSpace;
}

J_COLOR_SPACE JpegHandler::getColorSpace() const
{
	return colorSpace;
}

int JpegHandler::getNumComponents() const
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
