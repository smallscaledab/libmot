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
		for(Segment* segment : segments)
		{
			cout << "segment: " << bytes_to_hex(segment->encode()) << endl;
		}
		//REQUIRE(bytes_to_hex(bytes) == "06 00 C4 79 04 EA 00" );
	}

	SECTION ("MOT_DIRECTORY_MODE") {
		string data("====");
		vector<unsigned char> bytes;
		copy(data.begin(), data.end(), back_inserter(bytes));

		SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance();
		MotObject o(id->next(), "TestObject", bytes, ContentTypes::Text::ASCII);
		o.addParameter(new MimeType("test/thing"));
		vector<MotObject*> objects;
		objects.push_back(&o);
		vector<DirectoryParameter*> params;
		params.push_back(new SortedHeaderInformation());
		SegmentEncoder encoder;
		vector<Segment*> segments = encoder.encode(id->next(), objects, params);
		for(Segment* segment : segments)
		{
			cout << "segment: " << bytes_to_hex(segment->encode()) << endl;
		}
		//REQUIRE(bytes_to_hex(bytes) == "06 00 C4 79 04 EA 00" );
	}

}
