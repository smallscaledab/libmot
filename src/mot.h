#ifndef MOT_H_
#define MOT_H_

#define MAX_SEGMENT_SIZE 8189 // maximum data segment size in bytes

#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "charsets.h"
#include "util.h"

using namespace std;

namespace mot {

	struct ContentType
	{
		int type;
		int subtype;
	};

    class Parameter
    {

    public:

		Parameter(int id);

		virtual ~Parameter() = 0;

        std::vector<unsigned char> encode();

		virtual std::vector<unsigned char> encodeData() const = 0;

		int getId() const { return id; };

    private:

        int id;

    };

	class HeaderParameter : public Parameter
	{

	public:

		HeaderParameter(int id);

		virtual ~HeaderParameter() = 0;

		bool operator== (const HeaderParameter &other)
		{
			return equals(other);
		}


	protected:

		virtual bool equals(const HeaderParameter& a) const = 0;

	};

	class ContentName : public HeaderParameter
	{

	public:

		ContentName(const std::string &name, Charset charset = Charsets::ISO::Latin1);

		vector<unsigned char> encodeData() const;

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		std::string name;

		Charset charset;

	};

	class MimeType : public HeaderParameter
	{

	public:

		MimeType(const std::string &mimetype);

		vector<unsigned char> encodeData() const;

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		std::string mimetype;

	};

	class RelativeExpiration : public HeaderParameter
	{

	public:

		RelativeExpiration(long offset);

		vector<unsigned char> encodeData() const;

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		long offset;

	};

	class AbsoluteExpiration : public HeaderParameter
	{

	public:

		AbsoluteExpiration(long timepoint);

		vector<unsigned char> encodeData() const;

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

		vector<unsigned char> encodeData() const;

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		CompressionType type;
	};

	class Priority : public HeaderParameter
	{

	public:

		Priority(unsigned short int priority);

		vector<unsigned char> encodeData() const;

	protected:

		bool equals(const HeaderParameter& a) const;

	private:

		unsigned short int priority;
	};

	class DirectoryParameter : public Parameter
	{

	public:

		DirectoryParameter(int id);

		virtual ~DirectoryParameter() = 0;

		bool operator== (const DirectoryParameter &other)
		{
			return equals(other);
		}

	protected:

		virtual bool equals(const DirectoryParameter& a) const = 0;

	};

	class SortedHeaderInformation : public DirectoryParameter
	{

	public:

		SortedHeaderInformation();

	protected:

		bool equals(const DirectoryParameter& a) const { return true; }

		vector<unsigned char> encodeData() const;

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

		static SequentialTransportIdGenerator* getInstance(int initial = 1)
		{
			if(!instance) instance = new SequentialTransportIdGenerator(initial);
			return instance;
		}

		int next();


	protected:

		~SequentialTransportIdGenerator() { };

	private:

		SequentialTransportIdGenerator(int initial);

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

		MotObject(int transportId, ContentName &name, const std::vector<unsigned char> & body, ContentType type);

		MotObject(int transportId, std::string &name, const std::vector<unsigned char> &body, ContentType type);

		MotObject(int transportId, const char *name, const std::vector<unsigned char> &body, ContentType type);

		MotObject(int transportId, ContentName &name, ContentType type);

		MotObject(int transportId, std::string &name, ContentType type);

		MotObject(int transportId, const char *name, ContentType type);

		/**
		 * @brief Adds a parameter
		 */
		void addParameter(HeaderParameter *parameter);

		/**
		 * @brief Returns all parameters
		 */
		std::vector<HeaderParameter*> getParameters() const { return parameters; };

		template <typename T>
		std::vector<HeaderParameter*> getParameterByType();

		template <typename T>
		bool hasParameter();

		void removeParameter(HeaderParameter& parameter);

		int getTransportId() const { return transportId; };

		ContentName getName() const { return name; };

		ContentType getType() const { return type; };

        std::vector<unsigned char> encodeHeader() const;

		std::vector<unsigned char> getBody() const { return body; };

	private:

		ContentType type;

		ContentName name;

		std::vector<unsigned char> body;

		std::vector<HeaderParameter*> parameters;

		int transportId;

	};

	typedef int SegmentDatagroupType;
	class SegmentDatagroupTypes
	{
	public:
		static const SegmentDatagroupType Header = 3;
		static const SegmentDatagroupType Body = 4;
		static const SegmentDatagroupType Directory_Uncompressed = 6;
		static const SegmentDatagroupType Directory_Compressed = 7;
	};

	class Segment
	{

	public:

		/**
		 * @brief MOT segment
		 * @param object Source MOT object
		 * @param data Encoded segment data
		 * @param index Segment index
		 * @param repetition Remaining repetitions (>6=indefinite)
		 * @param type Segment data type
		 * @param last True if this is the last segment of this type (header or body)
		 */
		Segment(int transportId, const std::vector<unsigned char> & data, int index, int repetition, SegmentDatagroupType type, bool last = false);

		std::vector<unsigned char> encode() const;

		int getIndex() const { return index; };

		int getRepetition() const { return repetition; };

		SegmentDatagroupType getType() const { return type; };

		bool isLast() const { return last; };

		int getSize() const { return data.size(); };

		int getTransportId() const { return transportId; };

	private:

		int index;

		int repetition;

		SegmentDatagroupType type;

		bool last;

		std::vector<unsigned char> data;

		int transportId;

	};

	class SegmentationStrategy
	{

	public:

		virtual int getSegmentSize() = 0;

		virtual int getSegmentSize(const MotObject &object) = 0;
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

		int getSegmentSize();

		int getSegmentSize(const MotObject &object);

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

		/**
		 * Segment a single MOT object in MOT Header Mode
		 * @param object MOT object to encode
		 */
		vector<Segment> encode(const MotObject &object);

		/**
		 * Segment s directory of MOT objects in MOT directory Mode
		 */
		vector<Segment> encode(int transportId, const vector<MotObject> &objects);

		vector<Segment> encode(int transportId, const vector<MotObject> &objects, vector<DirectoryParameter*> parameters);

	private:

		SegmentationStrategy* strategy;

		vector<vector<unsigned char> > chunk_segments(vector<unsigned char> data, int chunk_size);

	};

}

#endif /* MOT_H_ */
