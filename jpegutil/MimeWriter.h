#ifndef MIMEWRITER_H_
#define MIMEWRITER_H_

#include "MimeParser.h"

namespace jpegutil
{

class MimeWriter: public MimeParser
{
public:
	MimeWriter();
	virtual ~MimeWriter();
};

}

#endif // MIMEWRITER_H_
