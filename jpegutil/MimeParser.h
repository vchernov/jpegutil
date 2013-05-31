#ifndef MIMEPARSER_H_
#define MIMEPARSER_H_

#include <string>
#include <vector>

namespace jpegutil
{

/**
 * Parser of MIME containers (Motion JPEG or MJPEG format).
 */
class MimeParser
{
public:
	typedef std::vector<std::string> HeaderContainer;

	MimeParser();
	virtual ~MimeParser();

	void setBoundary(const std::string& boundary);
	const std::string& getBoundary() const;

protected:
	enum State
	{
		S_BOUNDARY,
		S_HEADER,
		S_CONTENT,
	};

	static const std::string endOfLine;
	static const std::string dash;

	std::string getOpenDelimiter() const;

	std::string boundary;
	std::string lengthHeader;
	std::string typeHeader;

private:
	// forbid copying
	MimeParser(const MimeParser&);
	void operator=(const MimeParser&);
};

}

#endif // MIMEPARSER_H_
