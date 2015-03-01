#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include "catch.hpp"
#include "mot.h"

using namespace mot;
using namespace std;

TEST_CASE( "MOT tests", "[mot]" ) {

	SECTION ("MOT_1") {
		string data("test data");
		vector<unsigned char> bytes;
		copy(data.begin(), data.end(), back_inserter(bytes));

		RandomTransportIdGenerator* id = RandomTransportIdGenerator::getInstance();
		MotObject o(id->next(), "TestObject", bytes);
		o.addParameter(new MimeType("test/thing"));
		cout << "transport id: " << o.getTransportId() << endl;
		SegmentEncoder encoder;
		vector<Segment*> segments = encoder.encode(&o);
		cout << "segments: " << segments.size() << endl;
		for(Segment* segment : segments)
		{
			cout << "segment: " << bytes_to_hex(segment->encode()) << endl;
		}
		//REQUIRE(bytes_to_hex(bytes) == "06 00 C4 79 04 EA 00" );
	}

}
