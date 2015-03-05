#ifndef MOT_H_
#define MOT_H_

#define MAX_SEGMENT_SIZE 8189 // maximum data segment size in bytes

#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "util.h"

using namespace std;

namespace mot {

	vector<unsigned char> timepoint_to_encoded_utc(int timepoint);

	int timepoint_to_mjd(int timepoint);

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

		virtual ~HeaderParameter() = 0;

		virtual std::vector<unsigned char> encode() = 0;

		bool operator== (const HeaderParameter &other)
		{
			return equals(other);
		}

		int getId() { return id; };

	protected:

		virtual bool equals(const HeaderParameter& a) const = 0;

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

		vector<unsigned char> encode();

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		std::string name;

		Charset charset;

	};

	class MimeType : public HeaderParameter
	{

	public:

		MimeType(std::string mimetype);

		vector<unsigned char> encode();

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		std::string mimetype;

	};

	class RelativeExpiration : public HeaderParameter
	{

	public:

		RelativeExpiration(long offset);

		vector<unsigned char> encode();

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		long offset;

	};

	class AbsoluteExpiration : public HeaderParameter
	{

	public:

		AbsoluteExpiration(long timepoint);

		vector<unsigned char> encode();

	protected:

		bool equals(const HeaderParameter& a) const;

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

		vector<unsigned char> encode();

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		CompressionType type;
	};

	class Priority : public HeaderParameter
	{

	public:

		Priority(unsigned short int priority);

		bool operator==(const Priority& other);

		vector<unsigned char> encode();

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		unsigned short int priority;
	};

	/**
	 * Interface for a Transport ID (TId) generator
	 *
	 * [transport ID explanation here]
	 */
	class TransportIdGenerator
	{

	public:

		virtual int next() = 0;

	};

	class SequentialTransportIdGenerator : public TransportIdGenerator
	{

	public:

		static SequentialTransportIdGenerator* getInstance()
		{
			if(!instance) instance = new SequentialTransportIdGenerator;
			return instance;
		}

		int next();

	protected:

		~SequentialTransportIdGenerator() { };

	private:

		SequentialTransportIdGenerator() : last(0) { };

		static SequentialTransportIdGenerator* instance;

		int last;

	};

	class RandomTransportIdGenerator : public TransportIdGenerator
	{

	public:

		static RandomTransportIdGenerator* getInstance()
		{
			if(!instance) instance = new RandomTransportIdGenerator;
			return instance;
		}

		int next();

	protected:

		~RandomTransportIdGenerator() { };

	private:

		RandomTransportIdGenerator() {
			srand(time(NULL));
		};

		static RandomTransportIdGenerator* instance;

		std::vector<int> ids;

	};

	class MotObject
	{

	public:

		MotObject(int transportId, ContentName name, std::vector<unsigned char> body, ContentType type = ContentTypes::General::Object_Transfer);

		MotObject(int transportId, std::string name, std::vector<unsigned char> body, ContentType type = ContentTypes::General::Object_Transfer);

		MotObject(int transportId, ContentName name, ContentType type = ContentTypes::General::Object_Transfer);

		MotObject(int transportId, std::string name, ContentType type = ContentTypes::General::Object_Transfer);


		/**
		 * @brief Adds a parameter
		 */
		void addParameter(HeaderParameter* parameter);

		/**
		 * @brief Returns all parameters
		 */
		std::vector<HeaderParameter*> getParameters() { return parameters; };

		template <typename T>
		std::vector<HeaderParameter*> getParameterByType();

		template <typename T>
		bool hasParameter();

		void removeParameter(HeaderParameter& parameter);

		int getTransportId() { return transportId; };

		ContentName getName() { return name; };

		ContentType getType() { return type; };

		std::vector<unsigned char> getBody() { return body; };

	private:

		ContentType type;

		ContentName name;

		std::vector<unsigned char> body;

		std::vector<HeaderParameter*> parameters;

		int transportId;

	};

	class Segment
	{

	public:

		/**
		 * @brief MOT segment
		 * @param object Source MOT object
		 * @param data Encoded segment data
		 * @param repetition Remaining repetitions (>6=indefinite)
		 */
		Segment(MotObject* object, std::vector<unsigned char> data, int repetition);

		std::vector<unsigned char> encode();

		int getRepetition() { return repetition; };

		int getSize() { return data.size(); };

	private:

		int repetition;

		std::vector<unsigned char> data;

		MotObject* object;

	};

	class SegmentationStrategy
	{

	public:

		virtual int getSegmentSize(MotObject* object) = 0;
	};

	/**
	 * A strategy which will create all segments across all objects with
	 * a constant maximum segment size.
	 */
	class ConstantSizeSegmentationStrategy : public SegmentationStrategy
	{

	public:

		/**
		 * Creates the segmentation with a defined size
		 *
		 * @param size The maximum segment size to use in bytes, defaulting
		 * to the MAX_SEGMENT_SIZE (8189 bytes).
		 */
		ConstantSizeSegmentationStrategy(int size = MAX_SEGMENT_SIZE);

		int getSegmentSize(MotObject* object);

	private:

		int size;

	};

	/**
	 * Segmentation engine (see ETSI EN 301 234 v2.1.1, Section 5.1)
	 *
	 * Will take MOT object entities and segment them up into data segments
	 * of equal size. Only the last segment may be of a smaller size.
	 *
	 * Segmentation will apply separately to the MOT header and MOT body
	 * objects, mapping each segment to an MSC datagroup.
	 */
	class SegmentEncoder
	{

	public:

		SegmentEncoder(SegmentationStrategy* strategy = new ConstantSizeSegmentationStrategy());

		std::vector<Segment*> encode(MotObject* object);

	private:

		SegmentationStrategy* strategy;

		vector<vector<unsigned char> > chunk_segments(vector<unsigned char> data, int chunk_size);

	};

}

#endif /* MOT_H_ */
