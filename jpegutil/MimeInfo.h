#ifndef MIMEINFO_H_
#define MIMEINFO_H_

#include <string>

namespace jpegutil {

/**
 * Information for MIME container.
 */
class MimeInfo {
public:
    static const std::string endOfLine;
    static const std::string dash;

    MimeInfo();
    virtual ~MimeInfo();

    const std::string& getBoundary() const;
    void setBoundary(const std::string& boundary);

    std::string getOpenDelimiter() const;

    const std::string& getTypeHeader() const;
    void setTypeHeader(const std::string& typeHeader);

    const std::string& getLengthHeader() const;
    void setLengthHeader(const std::string& lengthHeader);

private:
    std::string boundary;

    std::string typeHeader;
    std::string lengthHeader;
};

}

#endif // MIMEINFO_H_
