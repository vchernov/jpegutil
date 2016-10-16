#include "MimeWriter.h"

namespace jpegutil {

MimeWriter::MimeWriter(MimeInfo* mimeInfo) : info(mimeInfo) {
}

MimeWriter::~MimeWriter() {
}

MimeInfo* MimeWriter::getMimeInfo() const {
    return info;
}

void MimeWriter::write(uint8_t* content, size_t len, const std::string& type, FILE* file) {
    // boundary
    std::string openDelimiter = info->getOpenDelimiter();
    fwrite(openDelimiter.c_str(), 1, openDelimiter.length(), file);

    // headers
    fprintf(file, "%s: %s%s", info->getTypeHeader().c_str(), type.c_str(), MimeInfo::endOfLine.c_str());
    fprintf(file, "%s: %lu%s", info->getLengthHeader().c_str(), (unsigned long)len, MimeInfo::endOfLine.c_str());
    fwrite(MimeInfo::endOfLine.c_str(), 1, MimeInfo::endOfLine.length(), file);

    // content
    fwrite(content, 1, len, file);

    // separator
    fwrite(MimeInfo::endOfLine.c_str(), 1, MimeInfo::endOfLine.length(), file);
}

}
