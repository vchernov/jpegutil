#ifndef MIMEWRITER_H_
#define MIMEWRITER_H_

#include <stdio.h>
#include <stdint.h>
#include <string>

#include "MimeInfo.h"

namespace jpegutil {

class MimeWriter {
public:
    MimeWriter(MimeInfo* mimeInfo);
    virtual ~MimeWriter();

    MimeInfo* getMimeInfo() const;

    void write(uint8_t* content, size_t len, const std::string& type, FILE* file);

private:
    MimeInfo* info;
};

}

#endif // MIMEWRITER_H_
