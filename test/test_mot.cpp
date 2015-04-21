#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include "catch.hpp"
#include "mot.h"

using namespace mot;
using namespace std;

TEST_CASE( "MOT encoding tests", "[mot]" ) {

	SECTION ("MOT_HEADER_MODE") {
		string data("====");
		vector<unsigned char> bytes;
		copy(data.begin(), data.end(), back_inserter(bytes));

		SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance();
		MotObject o(id->next(), "TestObject", bytes, ContentTypes::Text::ASCII);
		o.addParameter(new MimeType("test/thing"));
		SegmentEncoder encoder;
		vector<Segment*> segments = encoder.encode(o);

		REQUIRE(segments.size() == 2);
		REQUIRE(bytes_to_hex(segments.at(0)->encode()) == "00 20 00 00 00 40 0C 82 00 CC 0B 40 54 65 73 74 4F 62 6A 65 63 74 D0 0A 74 65 73 74 2F 74 68 69 6E 67");
		REQUIRE(bytes_to_hex(segments.at(1)->encode()) == "00 04 3D 3D 3D 3D");
	}

	SECTION ("MOT_DIRECTORY_MODE") {
		string data("*****");
		vector<unsigned char> bytes;
		copy(data.begin(), data.end(), back_inserter(bytes));

		SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance();
		vector<MotObject> objects;

		// first object
		MotObject a(id->next(), "First", bytes, ContentTypes::Text::ASCII);
		a.addParameter(new MimeType("test/thing"));
		objects.push_back(a);

		// second object
		MotObject b(id->next(), "Second", bytes, ContentTypes::Text::ASCII);
		b.addParameter(new MimeType("test/thing"));
		objects.push_back(b);

		// first object
		MotObject c(id->next(), "Third", bytes, ContentTypes::Text::ASCII);
		c.addParameter(new MimeType("test/thing"));
		objects.push_back(c);

		// directory
		vector<DirectoryParameter*> params;
		params.push_back(new SortedHeaderInformation());

		SegmentEncoder encoder;
		vector<Segment*> segments = encoder.encode(id->next(), objects, params);
		for(Segment* segment : segments)
		{
			cout << "segment: " << bytes_to_hex(segment->encode()) << endl;
		}
	}

}