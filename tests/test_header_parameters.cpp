#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include <mot.h> 

#include "catch.hpp"

using namespace mot;
using namespace std;

TEST_CASE( "MOT parameter encoding tests", "[motparams]" ) {

	SECTION ("TIMEPOINT") {
        vector<unsigned char> bytes = timepoint_to_encoded_utc(1442684842);
		REQUIRE(bytes_to_hex(bytes) == "B7 F1 0C 6F 58 00");
	}

}
