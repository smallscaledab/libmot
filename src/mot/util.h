#ifndef MOT_UTIL_H_
#define MOT_UTIL_H_

#include <vector>
#include <bitset>

using namespace std;

template<size_t size>
inline std::vector<unsigned char> bits_to_bytes(std::bitset<size> bits)
{
    std::vector<unsigned char> bytes(size/8);
    for(int j=0; j<int(size); j++) {
        bytes[j/8] = bytes[j/8] + ((bits[size-j-1] ? 1:0) << (7-j%8));
    }

    return bytes;
}

char const h[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

inline std::string bytes_to_hex(std::vector<unsigned char> bytes)
{
    std::string str;
    for(int i = 0; i < (int)bytes.size(); i++) {
        unsigned char c = bytes.at(i);
        str += (h[(c & 0xF0) >> 4]);
        str += (h[c & 0x0F]);
        if(i < (int)bytes.size() - 1) str += (' ');
    }
    return str;
}

template <int size>
inline std::bitset<size> bitstring_to_bits(std::string string)
{
    std::bitset<size> bits;
    for(int i=0; i < bits.count(); i++) {
        bits.setBit(i, string[i] == '0' ? false : true);
    }
    return bits;
}

inline std::vector<unsigned char> operator+(const std::vector<unsigned char> &a, const std::vector<unsigned char> &b)
{
    std::vector<unsigned char> result(b);
    result.insert(result.begin(), a.begin(), a.end());
    return result;
}

inline std::ostream& operator<< (std::ostream& stream, const std::vector<unsigned char> bytes) {
    std::string text(bytes.begin(), bytes.end());
    stream << text;
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const std::bitset<8>& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); ++i)
        text.insert(0, bits[i] ? "1": "0");
    stream << text;
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const std::bitset<16>& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); ++i)
        text.insert(0, bits[i] ? "1": "0");
    stream << text;
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const std::bitset<24>& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); ++i)
        text.insert(0, bits[i] ? "1": "0");
    stream << text;
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const std::bitset<32>& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); ++i)
        text.insert(0, bits[i] ? "1": "0");
    stream << text;
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const std::bitset<48>& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); ++i)
        text.insert(0, bits[i] ? "1": "0");
    stream << text;
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const std::bitset<56>& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); ++i)
        text.insert(0, bits[i] ? "1": "0");
    stream << text;
    return stream;
}

inline std::ostream& operator<< (std::ostream& stream, const std::bitset<64>& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); ++i)
        text.insert(0, bits[i] ? "1": "0");
    stream << text;
    return stream;
}

#endif // MOT_UTIL_H
