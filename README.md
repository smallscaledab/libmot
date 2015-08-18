libmot
======

Encoder/Decoder for MOT objects as per ETSI EN 301 234 .

# Current Status

Encoding of objects and parameters into Segmented data.

# TODO

# Examples

Encoding a simple text MOT object into Datagroups and write out the resultant data to the console.

```cpp
#include <vector>
#include <iostream>

#include "mot.h"

using namespace mot;

int main() {
    string data("=====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));
    SequentialTransportIdGenerator::initial = 8541;
    SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance();
    int transportId = id->next();
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.addParameter(new MimeType("application/txt"));
    SegmentEncoder encoder;
    vector<Segment*> segments = encoder.encode(o);
    for(Segment* segment : segments)
    {
        cout << segment->encode();
    }
    return  0;
}
```

# building

automake --add-missing
