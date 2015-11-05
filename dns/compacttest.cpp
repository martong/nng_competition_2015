#include "compact.hpp"

#include <iostream>

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}


std::string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

int main() {
    // input length must be divisible by 4
    std::string str = "AAAACCCCGGGGTTTT";
    std::string compressed4 = cCompress4(str);
    std::string decompressed4 = cDecompress4(compressed4);

    std::cout << (decompressed4 == str) << ' ' << str << " '"
              << string_to_hex(compressed4) << "' '" << decompressed4
              << "' " << std::endl;

    std::string compressed2 = cCompress2(str);
    std::string decompressed2 = cDecompress2(compressed2);

    std::cout << (decompressed2 == str) << ' ' << str << " '"
              << string_to_hex(compressed2) << "' '" << decompressed2
              << "' " << std::endl;
}
