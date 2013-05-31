#include "MimeReader.h"

#include <iostream>
#include <limits>

namespace jpegutil
{

MimeReader::MimeReader()
{
	init();
}

MimeReader::~MimeReader()
{
}

void MimeReader::init()
{
	state = S_BOUNDARY;
	contentLength = std::numeric_limits<size_t>::max();
	contentType = "";

	headers.clear();
	headerBuffer.str("");
	headerBuffer.clear();

	target = "";
	targetInd = 0;
}

void MimeReader::parse(char c)
{
	// lazy initialization of the search target
	if (target.empty())
	{
		switch (state)
		{
		case S_BOUNDARY:
			target = getOpenDelimiter();
			targetInd = 0;
			break;
		case S_HEADER:
			target = endOfLine;
			targetInd = 0;
			break;
		default:
			break;
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
			std::string header = headerBuffer.str();
			headers.push_back(header);
			headerBuffer.str("");
			headerBuffer.clear();

			if (!headers.empty())
			{
				if (headers[headers.size() - 1] == endOfLine)
				{
					parseHeaders(headers);
					state = S_CONTENT;
				}
			}
		}
		break;
	case S_CONTENT:
		if (contentLength == 0)
			state = S_BOUNDARY;
		break;
	default:
		std::cerr << "unknown state of MimeParser: " << state << std::endl;
		break;
	}
}

void MimeReader::parseHeaders(const HeaderContainer& headersData)
{
	HeaderContainer::const_iterator it = headersData.begin();
	HeaderContainer::const_iterator end = headersData.end();
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
}

}
