#include <vector>
#include <iostream>

#include <mot.h> 
#include <mot/util.h> 
#include <mot/contenttypes.h>

#include "test_util.h"

using namespace mot;
using namespace std;

int main()
{
    string data("*****");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    SequentialTransportIdGenerator id(8124);
    vector<MotObject> objects;

    // first object
    MotObject a(id.Next(), "First", bytes, ContentTypes::Text::ASCII);
    a.AddParameter(new MimeType("test/thing"));
    objects.push_back(a);

    // second object
    MotObject b(id.Next(), "Second", bytes, ContentTypes::Text::ASCII);
    b.AddParameter(new MimeType("test/thing"));
    objects.push_back(b);

    // first object
    MotObject c(id.Next(), "Third", bytes, ContentTypes::Text::ASCII);
    c.AddParameter(new MimeType("test/thing"));
    objects.push_back(c);

    // directory
    vector<DirectoryParameter*> params;
    params.push_back(new SortedHeaderInformation());

    SegmentEncoder encoder;
    vector<Segment> segments = encoder.Encode(id.Next(), objects, params);

    if(segments.size() != 4) return 1;
    ASSERT("header segment", bytes_to_hex(segments.at(0).Encode()), 
    "00 66 00 00 00 66 00 03 00 00 00 00 00 00 01 00 1F BC 00 00 00 50 0D 82 00 CC 06 40 46 69 72 73 74 D0 0A 74 65 73 74 2F 74 68 69 6E 67 1F BD 00 00 00 50 0E 02 00 CC 07 40 53 65 63 6F 6E 64 D0 0A 74 65 73 74 2F 74 68 69 6E 67 1F BE 00 00 00 50 0D 82 00 CC 06 40 54 68 69 72 64 D0 0A 74 65 73 74 2F 74 68 69 6E 67");
    ASSERT("body segment 1", bytes_to_hex(segments.at(1).Encode()), "00 05 2A 2A 2A 2A 2A");
    ASSERT("body segment 2", bytes_to_hex(segments.at(2).Encode()), "00 05 2A 2A 2A 2A 2A");
    ASSERT("body segment 3", bytes_to_hex(segments.at(3).Encode()), "00 05 2A 2A 2A 2A 2A");

}
