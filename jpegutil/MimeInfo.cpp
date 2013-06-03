#include "MimeInfo.h"

namespace jpegutil
{

const std::string MimeInfo::endOfLine = "\r\n";
const std::string MimeInfo::dash = "--";

MimeInfo::MimeInfo()
{
	boundary = "myboundary";
}

MimeInfo::~MimeInfo()
{
}

const std::string& MimeInfo::getBoundary() const
{
	return boundary;
}

void MimeInfo::setBoundary(const std::string& boundary)
{
	this->boundary = boundary;
}

std::string MimeInfo::getOpenDelimiter() const
{
	return dash + boundary + endOfLine;
}

const MimeInfo::HeaderContainer& MimeInfo::getHeaders() const
{
	return headers;
}

void MimeInfo::addHeader(const std::string& header)
{
	headers.push_back(header);
}

void MimeInfo::clearHeaders()
{
	headers.clear();
}

} // namespace jpegutil
