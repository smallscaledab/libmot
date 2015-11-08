#include <vector>
#include <iostream>

#include <mot.h> 
#include <contenttypes.h>
#include "../src/util.h"

using namespace mot;
using namespace std;

int main()
{
    string data("*****");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8124);
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

    if(segments.size() != 4) return 1;
    if(bytes_to_hex(segments.at(0)->encode()) != "00 66 00 00 00 66 00 03 00 00 00 00 00 00 01 00 00 01 00 00 00 50 0D 82 00 CC 06 40 46 69 72 73 74 D0 0A 74 65 73 74 2F 74 68 69 6E 67 00 02 00 00 00 50 0E 02 00 CC 07 40 53 65 63 6F 6E 64 D0 0A 74 65 73 74 2F 74 68 69 6E 67 00 03 00 00 00 50 0D 82 00 CC 06 40 54 68 69 72 64 D0 0A 74 65 73 74 2F 74 68 69 6E 67") return 1;
    if(bytes_to_hex(segments.at(1)->encode()) != "00 05 2A 2A 2A 2A 2A") return 1;
    if(bytes_to_hex(segments.at(2)->encode()) != "00 05 2A 2A 2A 2A 2A") return 1;
    if(bytes_to_hex(segments.at(3)->encode()) != "00 05 2A 2A 2A 2A 2A") return 1;

}
