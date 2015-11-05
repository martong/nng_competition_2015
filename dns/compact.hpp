#ifndef DNS_COMPACT_HPP
#define DNS_COMPACT_HPP

//#include <iostream>
#include <map>
#include <string>

std::string cCompress4(std::string input) {
    std::map<char, char> dict{{'A',0},{'C',1},{'G',2},{'T',3}};
    std::string output;
    std::string::const_iterator it = input.cbegin();
    while (it != input.cend()) {
        // std::cout << *it << ' ' << output.size() << std::endl;
        output.push_back((char)(dict[*it++] << 6) + (dict[*it++] << 4) +
                (dict[*it++] << 2) + dict[*it++]);
    }
    return output;
}

std::string cCompress2(std::string input) {
    std::map<char, char> dict{{'A',0},{'C',1},{'G',2},{'T',3}};
    std::string output;
    std::string::const_iterator it = input.cbegin();
    while (it != input.cend()) {
        output.push_back((dict[*it++] << 6) + (dict[*it++] << 4));
    }
    return output;
}

std::string cDecompress4(std::string input) {
    std::map<char, char> dict{{0,'A'},{1,'C'},{2,'G'},{3,'T'}};
    std::string output;
    for (char c : input) {
        // int a1 = dict[(char)((c & 0b11000000) >> 6)];
        // int a2 = dict[(char)((c & 0b00110000) >> 4)];
        // int a3 = dict[(char)((c & 0b00001100) >> 2)];
        // int a4 = dict[(char)((c & 0b00000011))];
        // std::cout << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << std::endl;
        output.append(1, dict[(char)((c & 0b11000000) >> 6)]);
        output.append(1, dict[(char)((c & 0b00110000) >> 4)]);
        output.append(1, dict[(char)((c & 0b00001100) >> 2)]);
        output.append(1, dict[(char)((c & 0b00000011))]);
    }
    return output;
}

std::string cDecompress2(std::string input) {
    std::map<char, char> dict{{0,'A'},{1,'C'},{2,'G'},{3,'T'}};
    std::string output;
    for (char c : input) {
        output.append(1, dict[(char)((c & 0b11000000) >> 6)]);
        output.append(1, dict[(char)((c & 0b00110000) >> 4)]);
    }
    return output;
}

#endif // DNS_COMPACT_HPP
