#ifndef MIMEINFO_H_
#define MIMEINFO_H_

#include <string>
#include <vector>

namespace jpegutil
{

/**
 * Information for MIME container.
 */
class MimeInfo
{
public:
	typedef std::vector<std::string> HeaderContainer;

	static const std::string endOfLine;
	static const std::string dash;

	MimeInfo();
	virtual ~MimeInfo();

	const std::string& getBoundary() const;
	void setBoundary(const std::string& boundary);

	std::string getOpenDelimiter() const;

	const HeaderContainer& getHeaders() const;
	void addHeader(const std::string& header);
	void clearHeaders();

private:
	std::string boundary;
	HeaderContainer headers;
};

} // namespace jpegutil

#endif // MIMEINFO_H_
