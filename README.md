libmot
======

Encoder/Decoder for MOT objects as per ETSI EN 301 234 .

# Current Status

Encoding of MOT objects and parameters into Segmented data. 

Used in conjunction with the `libmsc` library (https://github.com/magicbadger/libmsc) to create MSC datagroups and packets from MOT objects.

Currently under development, so subject to changes and refactoring.

# TODO

* Add API documentation
* Decoding of MOT objects

# Examples

Encoding a simple text MOT object into Datagroups and write out the resultant data as hex pairs for each segment to the console.

```cpp
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
```

# building

autoreconf -if
./configure
make

# installing

make install

# uninstalling

make uninstall
