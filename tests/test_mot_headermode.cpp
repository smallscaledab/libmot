#include <vector>
#include <iostream>

#include <mot.h> 
#include <mot/util.h> 
#include <mot/contenttypes.h>

using namespace mot;
using namespace std;

int main()
{
    string data("====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    SequentialTransportIdGenerator id(8000);
    MotObject o(id.Next(), "TestObject", bytes, ContentTypes::Text::ASCII);
    o.AddParameter(new MimeType("test/thing"));
    SegmentEncoder encoder;
    vector<Segment> segments = encoder.Encode(o);

    if(segments.size() != 2) return 1;
    if(bytes_to_hex(segments.at(0).Encode()) != "00 20 00 00 00 40 10 02 00 CC 0B 40 54 65 73 74 4F 62 6A 65 63 74 D0 0A 74 65 73 74 2F 74 68 69 6E 67") return 1;
    if(bytes_to_hex(segments.at(1).Encode()) != "00 04 3D 3D 3D 3D") return 1;
}
