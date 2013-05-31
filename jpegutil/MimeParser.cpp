#include "MimeParser.h"

namespace jpegutil
{

const std::string MimeParser::endOfLine = "\r\n";
const std::string MimeParser::dash = "--";

MimeParser::MimeParser()
{
	boundary = "myboundary";
	lengthHeader = "Content-Length";
	typeHeader = "Content-Type";
}

MimeParser::~MimeParser()
{
}

void MimeParser::setBoundary(const std::string& boundary)
{
	this->boundary = boundary;
}

const std::string& MimeParser::getBoundary() const
{
	return boundary;
}

std::string MimeParser::getOpenDelimiter() const
{
	return dash + boundary + endOfLine;
}

}
