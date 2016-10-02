#include <vector>
#include <iostream>

#include <mot.h> 
#include <mot/util.h> 

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TextTestRunner.h>

using namespace mot;
using namespace std;

class EncodeHeaderParameterTest : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(EncodeHeaderParameterTest);
    CPPUNIT_TEST(testTimepointToMJD);
    CPPUNIT_TEST(testTimepointToEncodedUTC);
    CPPUNIT_TEST(testContentName1);
    CPPUNIT_TEST(testContentName2);
    CPPUNIT_TEST(testMimeType);
    CPPUNIT_TEST_SUITE_END();

    public:

    void testTimepointToMJD()
    {
        int mjd = timepoint_to_mjd(1429967901);
        CPPUNIT_ASSERT(mjd == 57137);
    }

    void testTimepointToEncodedUTC()
    {
        vector<unsigned char> bytes = timepoint_to_encoded_utc(1442684842);
        CPPUNIT_ASSERT(bytes_to_hex(bytes) == "B7 F1 0C 6F 58 00");
    }

    void testContentName1()
    {
        ContentName name1("Test Name");
        CPPUNIT_ASSERT(bytes_to_hex(name1.Encode()) == "CC 0A 40 54 65 73 74 20 4E 61 6D 65");
    }

    void testContentName2()
    {
        ContentName name2("Hårken Øflergürd");
        cout << bytes_to_hex(name2.Encode()) << endl;
        CPPUNIT_ASSERT(bytes_to_hex(name2.Encode()) ==  "");
    }

    void testMimeType()
    {
        MimeType mime1("image/png");
        CPPUNIT_ASSERT(bytes_to_hex(mime1.Encode()) == "D0 09 69 6D 61 67 65 2F 70 6E 67");
    }

};

int main()
{
    CppUnit::TextTestRunner runner;
    runner.addTest(EncodeHeaderParameterTest::suite());
    return (runner.run() ? 0 : 1);
};
