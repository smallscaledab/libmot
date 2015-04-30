#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include "catch.hpp"
#include "mot.h"

using namespace mot;
using namespace std;

TEST_CASE( "Transport ID tests", "[mot]" ) {

	SECTION ("SEQUENTIAL") {
		SequentialTransportIdGenerator::initial = 8000;
		SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance();
		REQUIRE(id->next() == 8000);
	}
	
}