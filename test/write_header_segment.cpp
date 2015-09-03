#include <vector>
#include <iostream>

#include "../src/mot.h"
#include "../src/contenttypes.h"

using namespace mot;
using namespace std;

int main()
{
    string data("====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8000);
    MotObject o(id->next(), "TestObject", bytes, ContentTypes::Text::ASCII);
    o.addParameter(new MimeType("test/thing"));
    SegmentEncoder encoder;
    vector<Segment> segments = encoder.encode(o);
    cout << segments.at(0).encode();
    return 0;
}
