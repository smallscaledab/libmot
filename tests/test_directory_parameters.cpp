#include <vector>
#include <iostream>

#include <mot.h>
#include <mot/util.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TextTestRunner.h>

using namespace mot;
using namespace std;

class EncodeDirectoryParameterTest : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(EncodeDirectoryParameterTest);
    CPPUNIT_TEST(testRelativeExpiration1);
    CPPUNIT_TEST(testRelativeExpiration2);
    CPPUNIT_TEST(testRelativeExpiration3);
    CPPUNIT_TEST(testRelativeExpiration4);
    CPPUNIT_TEST(testRelativeExpiration5);
    CPPUNIT_TEST(testCompression);
    CPPUNIT_TEST(testPriority);
    CPPUNIT_TEST(testSortedHeaderInformation);
    CPPUNIT_TEST_SUITE_END();

    public:

    void testRelativeExpiration1()
    {
        RelativeExpiration expiration1(30); // 30m relative expiration
        CPPUNIT_ASSERT("relative expiration 1: 30m", bytes_to_hex(expiration1.Encode()), "49 0F");
    }

    void testRelativeExpiration2()
    {
        RelativeExpiration expiration2(23*60); // 23h relative expiration
        CPPUNIT_ASSERT("relative expiration 2: 23h", bytes_to_hex(expiration2.Encode()), "49 6E");
    }

    void testRelativeExpiration3()
    {
        RelativeExpiration expiration3(4*24*60); // 4d relative expiration
        CPPUNIT_ASSERT("relative expiration 3: 4d", bytes_to_hex(expiration3.Encode()), "49 B0");
    }

    void testRelativeExpiration4()
    {
        RelativeExpiration expiration4(32*24*60); // 32d relative expiration
        CPPUNIT_ASSERT("relative expiration 4: 32d", bytes_to_hex(expiration4.Encode()), "49 E0");
    }

    void testRelativeExpiration5()
    {
        AbsoluteExpiration expiration5(1429967901);
        CPPUNIT_ASSERT("absolute expiration 4: 2015-04-25", bytes_to_hex(expiration5.Encode()), "C9 06 B7 CC 4B 52 54 00");
    }

    void testCompression()
    {   
        Compression compression(CompressionTypes::GZip);
        CPPUNIT_ASSERT("compression: gzip", bytes_to_hex(compression.Encode()), "51 01");
    }

    void testPriority()
    {   
        Priority priority(40);
        CPPUNIT_ASSERT("priority: 40", bytes_to_hex(priority.Encode()), "4A 28");
    }

    void testSortedHeaderInformation()
    {   
        SortedHeaderInformation sorted;
        CPPUNIT_ASSERT("sorted header information: true", bytes_to_hex(sorted.Encode()), "00");
    }

}

int main()
{
    CppUnit::TextTestRunner runner;
    runner.addTest(EncodeAttributeTest::suite());
    return (runner.run() ? 0 : 1);
}
