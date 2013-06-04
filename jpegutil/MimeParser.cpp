#include "MimeParser.h"

#include <stdexcept>

namespace jpegutil
{

MimeParser::MimeParser(MimeInfo* mimeInfo) :
	info(mimeInfo)
{
	if (mimeInfo == NULL)
		throw std::runtime_error("NULL argument: mimeInfo");

	content = NULL;
	contentSize = 0;

	typeHeader = "Content-Type";
	lengthHeader = "Content-Length";

	init();
}

MimeParser::~MimeParser()
{
	delete[] content;
}

void MimeParser::init()
{
	headerBuffer.str("");
	headerBuffer.clear();

	target = "";
	targetInd = 0;

	contentType = "";
	contentLength = 0;
	contentLoaded = 0;

	state = S_BOUNDARY;

	//*
	delete[] content;
	content = NULL;
	contentSize = 0;
	//*/
}

void MimeParser::parse(char c)
{
	// lazy initialization of the state specific parameters
	if (state == S_BOUNDARY)
	{
		if (target.empty())
		{
			target = info->getOpenDelimiter();
			targetInd = 0;
		}
	}
	if (state == S_HEADER)
	{
		if (target.empty())
		{
			target = MimeInfo::endOfLine;
			targetInd = 0;
		}
	}

	// searching of the target string
	bool targetFound = false;
	if (!target.empty())
	{
		if (c == target[targetInd])
			targetInd++;
		else
			targetInd = 0;
		if (targetInd == target.length())
		{
			targetFound = true;
			target = "";
			targetInd = 0;
		}
	}

	switch (state)
	{
	case S_BOUNDARY:
		if (targetFound) // dash + boundary + end of line
			state = S_HEADER;
		break;
	case S_HEADER:
		headerBuffer << c;

		if (targetFound) // end of line
		{
			std::string line = headerBuffer.str();

			if (line == MimeInfo::endOfLine) // empty
			{
				parseHeaders(info->getHeaders());
				info->clearHeaders();
				state = S_CONTENT;
			}
			else
			{
				size_t usefulPart = line.length() - MimeInfo::endOfLine.length();
				std::string header = line.substr(0, usefulPart);
				info->addHeader(header);
			}

			headerBuffer.str("");
			headerBuffer.clear();
		}
		break;
	case S_CONTENT:
		if (contentLoaded < contentLength)
		{
			content[contentLoaded] = c;
			contentLoaded++;
			if (contentLoaded == contentLength)
				state = S_BOUNDARY;
		}
		else
			throw std::runtime_error("MIME content length is exceeded");
		break;
	default:
		throw std::runtime_error("unknown state of MimeParser");
	}
}

void MimeParser::parseHeaders(const MimeInfo::HeaderContainer& headers)
{
	MimeInfo::HeaderContainer::const_iterator it = headers.begin();
	MimeInfo::HeaderContainer::const_iterator end = headers.end();
	for (; it != end; ++it)
	{
		std::stringstream ss(*it);

		std::string descr;
		if (!std::getline(ss, descr, ':'))
			continue;

		if (descr == lengthHeader)
			ss >> contentLength;

		if (descr == typeHeader)
			ss >> contentType;
	}

	contentLoaded = 0;
	if (contentLength > contentSize)
	{
		delete[] content;
		content = new uint8_t[contentLength];
		contentSize = contentLength;
	}
}

bool MimeParser::readNext(char* buffer, size_t len, size_t& offset)
{
	//TODO: implement me
	for (; offset < len; offset++)
	{
		char c = buffer[offset];
		parse(c);
	}
	return false;
}

bool MimeParser::readNext(FILE* file)
{
	bool loaded = false;
	while (!feof(file))
	{
		if (state == S_CONTENT)
		{
			// content reading speed up
			size_t remLen = contentLength - contentLoaded;
			size_t readLen = fread(content + contentLoaded, 1, remLen, file);
			if (readLen == remLen)
			{
				contentLoaded += remLen;
				state = S_BOUNDARY;
			}
			loaded = true;
			break;
		}

		char c = fgetc(file);
		parse(c);
	}
	return loaded;
}

MimeInfo* MimeParser::getMimeInfo() const
{
	return info;
}

const uint8_t* MimeParser::getContent() const
{
	return isContentReady() ? content : NULL;
}

bool MimeParser::isContentReady() const
{
	return contentLoaded == contentLength;
}

size_t MimeParser::getContentLength() const
{
	return contentLength;
}

const std::string& MimeParser::getContentType() const
{
	return contentType;
}

} // namespace jpegutil
