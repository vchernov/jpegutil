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

	lengthHeader = "Content-Length";
	typeHeader = "Content-Type";

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

	contentLength = 0;
	contentType = "";

	delete[] content;
	content = NULL;
	contentSize = 0;
	loadedSize = 0;

	state = S_BOUNDARY;
}

void MimeParser::parse(char c)
{
	if (state == S_BOUNDARY)
	{
		// lazy initialization of the target string
		if (target.empty())
		{
			target = info->getOpenDelimiter();
			targetInd = 0;
		}
	}

	if (state == S_HEADER)
	{
		// lazy initialization of the target string
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
		if (loadedSize < contentLength)
		{
			content[loadedSize] = c;
			loadedSize++;
			if (loadedSize == contentLength)
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

	if (contentLength > contentSize)
	{
		delete[] content;
		content = new uint8_t[contentLength];
		contentSize = contentLength;
	}
}

bool MimeParser::readNext(char* buffer, size_t len, size_t& offset)
{
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
		if (state == S_CONTENT && contentLength > 0)
		{
			size_t remLen = contentLength - loadedSize;
			size_t readLen = fread(content + loadedSize, 1, remLen, file);
			if (readLen == remLen)
			{
				loadedSize += remLen;
				state = S_BOUNDARY;
				loaded = true;
			}
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
	return loadedSize == contentLength;
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
