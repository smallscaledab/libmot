#ifndef LIBMOT_OLD_MOT_H_
#define LIBMOT_OLD_MOT_H_

#include <vector>
#include <string>

struct ContentType
{
	int type;
	int subtype;
};
namespace ContentTypes
{
	// general data
	namespace General
	{
		const ContentType Object_Transfer = {0, 0};
		const ContentType MIME_HTTP = {0, 1};
	}

	// text
	namespace Text
	{
		const ContentType ASCII = {1, 0};
		const ContentType ISO = {1, 1};
		const ContentType HTML = {1, 2};
	}

	// image
	namespace Image
	{
		const ContentType GIF = {2, 0};
		const ContentType JFIF = {2, 1};
		const ContentType BMP = {2, 2};
		const ContentType PNG = {2, 3};
	}

	// audio
	namespace Audio
	{
		const ContentType MPEG1_L1 = {3, 0};
		const ContentType MPEG1_L2 = {3, 1};
		const ContentType MPEG1_L3 = {3, 2};
		const ContentType MPEG2_L1 = {3, 3};
		const ContentType MPEG2_L2 = {3, 4};
		const ContentType MPEG2_L3 = {3, 5};
		const ContentType PCM = {3, 6};
		const ContentType AIFF = {3, 7};
		const ContentType ATRAC = {3, 8};
		const ContentType ATRAC2 = {3, 9};
		const ContentType MPEG4 = {3, 10};
	}

	// video
	namespace Video
	{
		const ContentType MPEG1 = {4, 0};
		const ContentType MPEG2 = {4, 1};
		const ContentType MPEG4 = {4, 2};
		const ContentType H263 = {4, 3};
	}

	// MOT
	namespace MOT
	{
		const ContentType Update = {5, 0};
	}

	// system
	namespace System
	{
		const ContentType MHEG = {6, 0};
		const ContentType Java = {6, 1};
	}

}

class HeaderParameter
{

public:

	HeaderParameter(int id);

private:

	int id;

};

typedef int Charset;
namespace Charsets
{
	namespace EBU
	{
		const Charset Latin = 0;
		const Charset Latin_Common_Core = 1;
		const Charset Latin_Core = 2;
	}
	namespace ISO
	{
		const Charset Latin2 = 3;
		const Charset Latin1 = 4;
		const Charset IEC_10646 = 15;
	}
}

class ContentName : public HeaderParameter
{

public:

	ContentName(std::string name, Charset charset = Charsets::ISO::Latin1);

private:

	std::string name;

	Charset charset;

};

class MimeType : public HeaderParameter
{

public:

	MimeType(std::string mimetype);

private:

	std::string mimetype;

};

class RelativeExpiration : public HeaderParameter
{

public:

	RelativeExpiration(long offset);

private:

	long offset;

};

class AbsoluteExpiration : public HeaderParameter
{

public:

	AbsoluteExpiration(long timepoint);

private:

	long timepoint;

};

typedef int CompressionType;
namespace CompressionTypes
{
	const CompressionType Reserved = 0;
	const CompressionType GZip = 1;
}
class Compression : public HeaderParameter
{

public:

	Compression(CompressionType type);

private:

	CompressionType type;
};

class Priority : public HeaderParameter
{

public:

	Priority(unsigned short int priority);

private:

	unsigned short int priority;
};

class MotObject
{

public:

	MotObject(ContentName name, std::vector<unsigned char> body, ContentType type = ContentTypes::General::Object_Transfer);

	/**
	 * @brief Adds a parameter
	 */
	void addParameter(HeaderParameter parameter);

	/**
	 * @brief Returns all parameters
	 */
	std::vector<HeaderParameter> getParameters() { return parameters; };

	std::vector<HeaderParameter> getParameterByType();

	bool hasParameter();

	void removeParameter(HeaderParameter parameter) { };

	int getTransportId() { return transportId; };

	ContentName getName() { return name; };

	ContentType getType() { return type; };

	std::vector<unsigned char> getBody() { return body; };

private:

	ContentType type;

	ContentName name;

	std::vector<unsigned char> body;

	std::vector<HeaderParameter> parameters;

	int transportId;

};


#endif /* LIBMOT_OLD_MOT_H_ */
