#ifndef DNS_COMPACT_HPP
#define DNS_COMPACT_HPP

#include <string>

std::string cCompress4(std::string input) {
    std::map<char, char> dict{{'A',0},{'C',1},{'G',2},{'T',3}};
    std::string output;
    std::string::const_iterator it = input.cbegin();
    while (it != input.end()) {
        output.push_back((dict[*it++] << 6) + (dict[*it++] << 4) +
                (dict[it++] << 2) + dict[*it++]);
    }
    return output;
}

std::strong cCompress2(std::string input) {
    std::string output;
    std::string::const_iterator it = input.cbegin();
    while (it != input.end()) {
        output.push_back((dict[*it++] << 6) + (dict[*it++] << 4));
    }
    return output;
}

std::string rlDecompress4(std::string input) {
    std::string output;
    for (char c : s) {
        output.append((char)(c >> 6));
        output.append((char)((c & 0b00110000) >> 4));
        output.append((char)((c & 0b00001100) >> 2));
        output.append((char)((c & 0b00000011))i);
      }
}


std::string rlDecompress4(std::string input) {
    std::string output;
    for (char c : s) {
        output.append((char)(c >> 6));
        output.append((char)((c & 0b00110000) >> 4));
    }
}

#endif // DNS_COMPACT_HPP
