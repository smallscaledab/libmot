#include "mot.h"

MotObject::MotObject(ContentName name, std::vector<unsigned char> body, ContentType type)
	: name(name), body(body), type(type)
{ }

HeaderParameter::HeaderParameter(int id)
	: id(id)
{ }

ContentName::ContentName(std::string name, Charset charset)
	: HeaderParameter(12), name(name), charset(charset)
{ }

MimeType::MimeType(std::string mimetype)
	: HeaderParameter(16), mimetype(mimetype)
{ }

RelativeExpiration::RelativeExpiration(long offset)
	: HeaderParameter(4), offset(offset)
{ }

AbsoluteExpiration::AbsoluteExpiration(long timepoint)
	: HeaderParameter(4), timepoint(timepoint)
{ }

Priority::Priority(unsigned short int priority)
	: HeaderParameter(10), priority(priority)
{ }
