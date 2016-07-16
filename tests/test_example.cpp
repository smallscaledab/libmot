#include <vector>
#include <iostream>

#include <mot.h>
#include <mot/util.h>
#include <mot/contenttypes.h>

using namespace mot;

int main() {
    string data("=====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));
    int transportId = 8541; 
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.AddParameter(new MimeType("application/txt"));
    SegmentEncoder encoder;
    vector<Segment> segments = encoder.Encode(o);
    for(Segment segment : segments)
    {
        cout << bytes_to_hex(segment.Encode()) << endl;
    }
    return 0;
}
