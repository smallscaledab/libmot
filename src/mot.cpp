#include "mot.h"
#include "util.h"

#include <algorithm>

using namespace mot;

MotObject::MotObject(int transportId, ContentName name, std::vector<unsigned char> body, ContentType type)
	: transportId(transportId), name(name), body(body), type(type)
{ }

MotObject::MotObject(int transportId, std::string name, std::vector<unsigned char> body, ContentType type)
	: transportId(transportId), name(ContentName(name)), body(body), type(type)
{ }

MotObject::MotObject(int transportId, ContentName name, ContentType type)
	: transportId(transportId), name(name), type(type)
{ }

MotObject::MotObject(int transportId, std::string name, ContentType type)
	: transportId(transportId), name(ContentName(name)), type(type)
{ }

void MotObject::addParameter(const HeaderParameter& parameter)
{
	parameters.push_back(parameter);
}

template <typename T>
std::vector<HeaderParameter> MotObject::getParameterByType()
{
	std::vector<HeaderParameter> result;
//	for(HeaderParameter& parameter : parameters)
//	{
//		if(typeid(parameter) == typeid(T))
//		{
//			result.push_back(parameter);
//		}
//	}
	return result;
}

template <typename T>
bool MotObject::hasParameter()
{
//	for(HeaderParameter& parameter : parameters)
//	{
//		if(typeid(parameter) == typeid(T))
//		{
//			return true;
//		}
//	}
	return false;
}

void MotObject::removeParameter(HeaderParameter& parameter)
{
//	for(HeaderParameter& p : parameters)
//	{
//		if(parameter == p)
//		{
//			parameters.erase(std::find(parameters.begin(), parameters.end(), parameter));
//		}
//	}
};

HeaderParameter::HeaderParameter(int id)
	: id(id)
{ }

HeaderParameter::~HeaderParameter()
{ }

ContentName::ContentName(std::string name, Charset charset)
	: HeaderParameter(12), name(name), charset(charset)
{ }

bool ContentName::operator==(const ContentName& that)
{
	return (this->charset == that.charset &&
			this->name == that.name);

}

MimeType::MimeType(std::string mimetype)
	: HeaderParameter(16), mimetype(mimetype)
{ }

bool MimeType::operator==(const MimeType& that)
{
	return (this->mimetype == that.mimetype);
}

RelativeExpiration::RelativeExpiration(long offset)
	: HeaderParameter(4), offset(offset)
{ }

bool RelativeExpiration::operator==(const RelativeExpiration& that)
{
	return (this->offset == that.offset);
}

AbsoluteExpiration::AbsoluteExpiration(long timepoint)
	: HeaderParameter(4), timepoint(timepoint)
{ }

bool AbsoluteExpiration::operator==(const AbsoluteExpiration& that)
{
	return (this->timepoint == that.timepoint);
}

Priority::Priority(unsigned short int priority)
	: HeaderParameter(10), priority(priority)
{ }

bool Priority::operator==(const Priority& that)
{
	return (this->priority == that.priority);
}

Segment::Segment(MotObject* object, std::vector<unsigned char> data, int repetition)
	: object(object), data(data), repetition(repetition)
{ }

std::vector<unsigned char> Segment::encode() {

	std::bitset<8> bits(data.size() + // segment size (13)
				   repetition << 13); // repetition (3)

	std::vector<unsigned char> bytes = bits_to_bytes(bits);
    bytes.insert(bytes.begin(), data.begin(), data.end());
    return bytes;
}

SegmentEncoder::SegmentEncoder(const SegmentationStrategy& strategy)
	: strategy(strategy)
{ }

std::vector<Segment&> SegmentEncoder::encode(MotObject& object)
{
	std::vector<Segment&> segments;

	// segment body data
	std::vector<unsigned char> body_data = object.getBody();
	int i = 0;
//	while(i < body_data.length())
//	{
//
//	}

	return segments;


//
//# split body data into segments
//      body_data = object.get_body()
//      body_segments = _segment(body_data, segmenting_strategy)
//
//      # encode header extension parameters
//      extension_bits = bitarray()
//      for parameter in object.get_parameters():
//          extension_bits += parameter.encode()
//
//      # insert the core parameters into the header
//      bits = bitarray()
//      bits += int_to_bitarray(len(body_data) if body_data else 0, 28) # (0-27): BodySize in bytes
//      bits += int_to_bitarray(extension_bits.length() / 8 + 7, 13) # (28-40): HeaderSize in bytes (core=7 + extension)
//      bits += int_to_bitarray(object.get_type().type, 6)  # (41-46): ContentType
//      bits += int_to_bitarray(object.get_type().subtype, 9) # (47-55): ContentSubType
//      bits += extension_bits # (56-n): Header extension data
//      header_segments = _segment(bits.tobytes(), segmenting_strategy)
//
//      # add header datagroups
//      for i, segment in enumerate(header_segments):
//          header_group = Datagroup(object.get_transport_id(), HEADER, segment, i, i%16, last=True if i == len(header_segments) - 1 else False)
//          datagroups.append(header_group)
//
//      # add body datagroups
//      for i, segment in enumerate(body_segments):
//          body_group = Datagroup(object.get_transport_id(), BODY, segment, i, i%16, last=True if i == len(body_segments) - 1 else False)
//          datagroups.append(body_group)
//
//      return datagroups;



}

ConstantSizeSegmentationStrategy::ConstantSizeSegmentationStrategy(int size)
	: size(size)
{ }

int ConstantSizeSegmentationStrategy::getSegmentSize(MotObject* object) {
	return size;
}

int SequentialTransportIdGenerator::next()
{
	return ++last;
}

SequentialTransportIdGenerator* SequentialTransportIdGenerator::instance;

int RandomTransportIdGenerator::next()
{
	int next = rand() % (1<<16) + 1;
	while(std::find(ids.begin(), ids.end(), next) != ids.end())
	{
		int next = rand() % (1<<16) + 1;
	}
	ids.push_back(next);
	return next;
}

RandomTransportIdGenerator* RandomTransportIdGenerator::instance;
