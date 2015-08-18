#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include "catch.hpp"
#include "mot.h"

using namespace mot;
using namespace std;

TEST_CASE( "Transport ID tests", "[mot]" ) {

	SECTION ("SEQUENTIAL") {
		SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8000);
		REQUIRE(id->next() == 8000);
		REQUIRE(id->next() == 8001);
		REQUIRE(id->next() == 8002);
		REQUIRE(id->next() == 8003);
		REQUIRE(id->next() == 8004);
		REQUIRE(id->next() == 8005);
	}
	
}
