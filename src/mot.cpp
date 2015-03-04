#include "mot.h"
#include "util.h"

#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;
using namespace mot;

MotObject::MotObject(int transportId, ContentName name, vector<unsigned char> body, ContentType type)
	: transportId(transportId), name(name), body(body), type(type)
{ }

MotObject::MotObject(int transportId, string name, vector<unsigned char> body, ContentType type)
	: transportId(transportId), name(ContentName(name)), body(body), type(type)
{ }

MotObject::MotObject(int transportId, ContentName name, ContentType type)
	: transportId(transportId), name(name), type(type)
{ }

MotObject::MotObject(int transportId, string name, ContentType type)
	: transportId(transportId), name(ContentName(name)), type(type)
{ }

void MotObject::addParameter(HeaderParameter* parameter)
{
	parameters.push_back(parameter);
}

template <typename T>
vector<HeaderParameter*> MotObject::getParameterByType()
{
	vector<HeaderParameter*> result;
	for(HeaderParameter* parameter : parameters)
	{
		if(typeid(parameter) == typeid(T))
		{
			result.push_back(parameter);
		}
	}
	return result;
}

template <typename T>
bool MotObject::hasParameter()
{
	for(HeaderParameter* p : parameters)
	{
		if(typeid(p) == typeid(T))
		{
			return true;
		}
	}
	return false;
}
//
//void MotObject::removeParameter(HeaderParameter& parameter)
//{
//	parameters.erase(find(parameters.begin(), parameters.end(), parameter));
//};

HeaderParameter::HeaderParameter(int id)
	: id(id)
{ }

HeaderParameter::~HeaderParameter()
{ }

ContentName::ContentName(string name, Charset charset)
	: HeaderParameter(12), name(name), charset(charset)
{ }

bool ContentName::equals(const HeaderParameter& other) const
{
    const ContentName* that = dynamic_cast<const ContentName*>(&other);
    return that != nullptr && (this->charset == that->charset &&
			this->name == that->name);
}

vector<unsigned char> ContentName::encode()
{
	bitset<8> bits(charset); // charset(4)

	vector<unsigned char> bytes = bits_to_bytes(bits);
	copy(name.begin(), name.end(), back_inserter(bytes));

	return bytes;
}

MimeType::MimeType(string mimetype)
	: HeaderParameter(16), mimetype(mimetype)
{ }

bool MimeType::equals(const HeaderParameter& other) const
{
    const MimeType* that = dynamic_cast<const MimeType*>(&other);
    return that != nullptr && (this->mimetype == that->mimetype);
}

vector<unsigned char> MimeType::encode()
{
	vector<unsigned char> bytes;
	copy(mimetype.begin(), mimetype.end(), back_inserter(bytes));
	return bytes;
}

RelativeExpiration::RelativeExpiration(long offset)
	: HeaderParameter(4), offset(offset)
{ }

bool RelativeExpiration::equals(const HeaderParameter& other) const
{
    const RelativeExpiration* that = dynamic_cast<const RelativeExpiration*>(&other);
    return that != nullptr && (this->offset == that->offset);
}

vector<unsigned char> RelativeExpiration::encode()
{
	if(offset < (127 * 60)) // < 127m
	{
		bitset<8> bits(0 + // granularity(2)
			((offset/(2 * 60)) << 2)); // offset in 2 minute interval (6)
		return bits_to_bytes(bits);
	}
	else if(offset < (1891 * 60)) // < 1891m
	{
		bitset<8> bits(1 + // granularity(2)
					  ((offset/(30 * 60)) << 2)); // offset in 30 minute interval (6)
		return bits_to_bytes(bits);
	}
	else if(offset < (127 * 60 * 60)) // < 127h
	{
		bitset<8> bits(2 + // granularity(2)
					  ((offset/(2 * 60 * 60)) << 2)); // offset in 2 hour interval (6)
		return bits_to_bytes(bits);
	}
	else if(offset < (64 * 24 * 60 * 60)) // < 64d
	{
		bitset<8> bits(3 + // granularity(2)
					  ((offset/(24 * 60 * 60)) << 2)); // offset in day interval (6)
		return bits_to_bytes(bits);
	}

	return vector<unsigned char>(); // TODO raise exception
}

AbsoluteExpiration::AbsoluteExpiration(long timepoint)
	: HeaderParameter(4), timepoint(timepoint)
{ }

bool AbsoluteExpiration::equals(const HeaderParameter& other) const
{
    const AbsoluteExpiration* that = dynamic_cast<const AbsoluteExpiration*>(&other);
    return that != nullptr && (this->timepoint == that->timepoint);
}

vector<unsigned char> AbsoluteExpiration::encode()
{
	if(timepoint == 0) // NOW
	{
		bitset<32> bits(0);
		return bits_to_bytes(bits);
	}

	if(timepoint / (60000))
	{
		int mjd = timepoint_to_mjd(timepoint);
		bitset<48> bits(1  + // validity flag (1)
					   (mjd << 1) + // mjd (16)
					   (0) + // rfu (2)
					   (1 << 19) + // UTC flag
					   (timepoint << 20)); // timepoint (27)
		return bits_to_bytes(bits);
	}
	else
	{
		int mjd = timepoint_to_mjd(timepoint);
		bitset<32> bits(1  + // validity flag (1)
					   (mjd << 1) + // mjd (16)
					   (0) + // rfu (2)
					   (1 << 19) + // UTC flag
					   ((timepoint / 60000) << 20)); // timepoint (11)
		return bits_to_bytes(bits);
	}
}

Compression::Compression(CompressionType type)
	: HeaderParameter(17), type(type)
{ }

vector<unsigned char> Compression::encode()
{
	bitset<8> bits(type);
	return bits_to_bytes(bits);
}

bool Compression::equals(const HeaderParameter& other) const
{
    const Compression* that = dynamic_cast<const Compression*>(&other);
    return that != nullptr && (this->type == that->type);
}

Priority::Priority(unsigned short int priority)
	: HeaderParameter(10), priority(priority)
{ }

bool Priority::operator==(const Priority& that)
{
	return (this->priority == that.priority);
}

vector<unsigned char> Priority::encode()
{
	bitset<8> bits(priority);
	return bits_to_bytes(bits);
}

bool Priority::equals(const HeaderParameter& other) const
{
    const Priority* that = dynamic_cast<const Priority*>(&other);
    return that != nullptr && (this->priority == that->priority);
}

Segment::Segment(MotObject* object, vector<unsigned char> data, int repetition)
	: object(object), data(data), repetition(repetition)
{ }

vector<unsigned char> Segment::encode() {

	bitset<16> bits(data.size() + // segment size (13)
				   (repetition << 13)); // repetition (3)

	cout << "segment size: " << data.size() << endl;
	cout << "segment header: " << bits << endl;

	vector<unsigned char> bytes = bits_to_bytes(bits);
    bytes.insert(bytes.end(), data.begin(), data.end());
    return bytes;
}

SegmentEncoder::SegmentEncoder(SegmentationStrategy* strategy)
	: strategy(strategy)
{ }

vector<Segment*> SegmentEncoder::encode(MotObject* object)
{
	vector<Segment*> segments;

	int chunk_size = strategy->getSegmentSize(object);

	// segment header data
	vector<unsigned char> header_data;
	header_data = header_data + object->getName().encode();
	for(HeaderParameter* param : object->getParameters())
	{
		header_data = header_data + param->encode();
	}
	bitset<56> core_header_bits(object->getType().subtype + // content subtype (9)
							   (object->getType().type << 9) + // content type (6))
							   (header_data.size() << 15) + // header size (13)
							   (object->getBody().size() << 28)); // body size (28)
	vector<unsigned char> core_header_data = bits_to_bytes(core_header_bits);
	header_data.insert(header_data.begin(), core_header_data.begin(), core_header_data.end());
	for(vector<unsigned char> chunk : chunk_segments(header_data, chunk_size))
	{
		segments.push_back(new Segment(object, chunk, 1));
	}

	// segment body data
	vector<unsigned char> body_data = object->getBody();
	cout << "body data size : " << body_data.size() << endl;
	for(vector<unsigned char> chunk : chunk_segments(body_data, chunk_size))
	{
		segments.push_back(new Segment(object, chunk, 1));
	}

	return segments;
}

vector<vector<unsigned char> > SegmentEncoder::chunk_segments(vector<unsigned char> data, int chunk_size)
{
	vector<vector<unsigned char> > chunks;

	vector<unsigned char>::iterator start, end;
	start = end = data.begin();
	while(end != data.end())
	{
		int b = distance(end, data.end());
		int step = min(chunk_size, b);
		advance(end, step);
		vector<unsigned char> chunk(end - start);
		copy(start, end, chunk.begin());
		advance(start, step);
		chunks.push_back(chunk);
	}

	return chunks;
}

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
//
//
//
//}

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
	while(find(ids.begin(), ids.end(), next) != ids.end())
	{
		int next = rand() % (1<<16) + 1;
	}
	ids.push_back(next);
	return next;
}

RandomTransportIdGenerator* RandomTransportIdGenerator::instance;

int mot::timepoint_to_mjd(int timepoint)
{
	time_t t = timepoint / 1000;

	struct tm *tm;
	tm = gmtime(&t);

	int day = tm->tm_yday;
	int month = tm->tm_mon;
	int year = tm->tm_year + 1900;

	int yearp = 0;
	int monthp = 0;
	if(month == 1 || month == 2)
	{
		yearp = year - 1;
		monthp = month + 12;
	} else {
		yearp = year;
		monthp = month;
	}

	int A, B = 0;
	if  ((year < 1582) ||
		(year == 1582 && month < 10) ||
		(year == 1582 && month == 10 && day < 15))
	{
		B = 0;
	} else {
		A = trunc(yearp / 100.0);
		B = 2 - A + trunc(A / 4.0);
	}

	int C = 0;
	if(yearp < 0)
	{
		C = trunc((365.25 * yearp) - 0.75);
	} else {
		C = trunc(365.25 * yearp);
	}

	int D = trunc(30.6001 * (monthp + 1));

	int jd = B + C + D + day + 1720994.5;
	int mjd = jd - 2400000.5;

	return mjd;
}
