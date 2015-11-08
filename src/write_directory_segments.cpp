#include <vector>
#include <iostream>

#include "../src/mot.h"
#include "../src/contenttypes.h"

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

    // third object
    MotObject c(id->next(), "Third", bytes, ContentTypes::Text::ASCII);
    c.addParameter(new MimeType("test/thing"));
    objects.push_back(c);

    // directory
    vector<DirectoryParameter*> params;
    params.push_back(new SortedHeaderInformation());

    SegmentEncoder encoder;
    vector<Segment*> segments = encoder.encode(id->next(), objects, params);

    cout << segments.at(0)->encode() << segments.at(1)->encode() << segments.at(2)->encode() << segments.at(3)->encode();

    return 0;
}
