#include <vector>
#include <iostream>

#include <mot.h> 
#include <mot/util.h> 

#include "test_util.h"

using namespace mot;
using namespace std;

int main()
{
    int mjd = timepoint_to_mjd(1429967901);
    ASSERT("timepoint to MJD", mjd, 57137);

    vector<unsigned char> bytes = timepoint_to_encoded_utc(1442684842);
    ASSERT("encode timepoint", bytes_to_hex(bytes), "B7 F1 0C 6F 58 00");

    ContentName name1("Test Name");
    ASSERT("encode ASCII content name 1", bytes_to_hex(name1.Encode()), "CC 0A 40 54 65 73 74 20 4E 61 6D 65");

    ContentName name2("Hårken Øflergürd");
    //ASSERT("encode Non-ASCII content name 2", bytes_to_hex(name2.Encode()), "");

    MimeType mime1("image/png");
    ASSERT("encode MIME type 1", bytes_to_hex(mime1.Encode()), "D0 09 69 6D 61 67 65 2F 70 6E 67");

    // directory parameters
    RelativeExpiration expiration1(30); // 30m relative expiration
    ASSERT("relative expiration 1: 30m", bytes_to_hex(expiration1.Encode()), "49 0F");

    RelativeExpiration expiration2(23*60); // 23h relative expiration
    ASSERT("relative expiration 2: 23h", bytes_to_hex(expiration2.Encode()), "49 6E");

    RelativeExpiration expiration3(4*24*60); // 4d relative expiration
    ASSERT("relative expiration 3: 4d", bytes_to_hex(expiration3.Encode()), "49 B0");

    RelativeExpiration expiration4(32*24*60); // 32d relative expiration
    ASSERT("relative expiration 4: 32d", bytes_to_hex(expiration4.Encode()), "49 E0");

    AbsoluteExpiration expiration5(1429967901); 
    ASSERT("absolute expiration 4: 2015-04-25", bytes_to_hex(expiration5.Encode()), "C9 06 B7 CC 4B 52 54 00");

    Compression compression1(CompressionTypes::GZip);
    ASSERT("compression: gzip", bytes_to_hex(compression1.Encode()), "51 01");

    Priority priority(40);
    ASSERT("priority: 40", bytes_to_hex(priority.Encode()), "4A 28");

    SortedHeaderInformation sorted;
    ASSERT("sorted header information: true", bytes_to_hex(sorted.Encode()), "00");
}
