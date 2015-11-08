#include <vector>
#include <iostream>

#include <mot.h> 
#include "../src/util.h"

using namespace mot;
using namespace std;

int main()
{
    vector<unsigned char> bytes = timepoint_to_encoded_utc(1442684842);
	return bytes_to_hex(bytes) != "B7 F1 0C 6F 58 00";
}
