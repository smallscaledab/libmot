#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include "catch.hpp"
#include "mot.h"

using namespace mot;

TEST_CASE( "MOT tests", "[mot]" ) {

	SECTION ("MOT_1") {
		RandomTransportIdGenerator* id = RandomTransportIdGenerator::getInstance();
		MotObject o(id->next(), "TestObject");
		o.addParameter(MimeType("test/thing"));
		std::cout << o.getTransportId();
		//REQUIRE(bytes_to_hex(bytes) == "06 00 C4 79 04 EA 00" );
	}

}
