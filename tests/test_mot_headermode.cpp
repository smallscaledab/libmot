#include <vector>
#include <iostream>

#include <mot.h> 
#include <mot/util.h> 
#include <mot/contenttypes.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TextTestRunner.h>

using namespace mot;
using namespace std;

class EncodeHeaderModeTest : public CppUnit::TestFixture 
{

    CPPUNIT_TEST_SUITE(EncodeHeaderModeTest);
    CPPUNIT_TEST(testEncodeHeaderMode);
    CPPUNIT_TEST_SUITE_END();

    void testEncodeHeaderMode()
    {
        string data("====");
        vector<unsigned char> bytes;
        copy(data.begin(), data.end(), back_inserter(bytes));

        SequentialTransportIdGenerator id(8000);
        MotObject o(id.Next(), "TestObject", bytes, ContentTypes::Text::ASCII);
        o.AddParameter(new MimeType("test/thing"));
        SegmentEncoder encoder;
        vector<Segment> segments = encoder.Encode(o);

        CPPUNIT_ASSERT(segments.size() == 2);
        CPPUNIT_ASSERT(bytes_to_hex(segments.at(0).Encode()) == "00 20 00 00 00 40 10 02 00 CC 0B 40 54 65 73 74 4F 62 6A 65 63 74 D0 0A 74 65 73 74 2F 74 68 69 6E 67");
        CPPUNIT_ASSERT(bytes_to_hex(segments.at(1).Encode()) == "00 04 3D 3D 3D 3D");
    }
};

int main()
{
    CppUnit::TextTestRunner runner;
    runner.addTest(EncodeHeaderModeTest::suite());
    return (runner.run() ? 0 : 1);
}
