#ifndef MIMEREADER_H_
#define MIMEREADER_H_

#include "MimeParser.h"

#include <sstream>

namespace jpegutil
{

class MimeReader: public MimeParser
{
public:
	MimeReader();
	virtual ~MimeReader();

	/**
	 * Sets to initial state.
	 */
	void init();

private:
	// forbid copying
	MimeReader(const MimeReader&);
	void operator=(const MimeReader&);

	void parse(char c);
	void parseHeaders(const HeaderContainer&);

	State state;

	std::string target; // current search target
	size_t targetInd; // next character index to search

	// collected header data
	std::stringstream headerBuffer;
	HeaderContainer headers;

	size_t contentLength;
	std::string contentType;
};

}

#endif // MIMEREADER_H_
