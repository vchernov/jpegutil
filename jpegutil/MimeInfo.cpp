#include "MimeInfo.h"

namespace jpegutil {

const std::string MimeInfo::endOfLine = "\r\n";
const std::string MimeInfo::dash = "--";

MimeInfo::MimeInfo() {
	boundary = "myboundary";

	typeHeader = "Content-Type";
	lengthHeader = "Content-Length";
}

MimeInfo::~MimeInfo() {
}

const std::string& MimeInfo::getBoundary() const {
	return boundary;
}

void MimeInfo::setBoundary(const std::string& boundary) {
	this->boundary = boundary;
}

std::string MimeInfo::getOpenDelimiter() const {
	return dash + boundary + endOfLine;
}

const std::string& MimeInfo::getTypeHeader() const {
	return typeHeader;
}

void MimeInfo::setTypeHeader(const std::string& typeHeader) {
	this->typeHeader = typeHeader;
}

const std::string& MimeInfo::getLengthHeader() const {
	return lengthHeader;
}

void MimeInfo::setLengthHeader(const std::string& lengthHeader) {
	this->lengthHeader = lengthHeader;
}

}
