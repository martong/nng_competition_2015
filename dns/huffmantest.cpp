#include "huffman.hpp"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <string>

int main() {
#if 0
    std::string input;
    input.append(1, (char)3);
    input.append(1, (char)24);
    std::map<std::pair<char, std::uint16_t>, char> cc{{{13, 'c'}, 'A'}};
    std::cout << decodeString(cc, 13, input) << std::endl;

    std::map<char, std::pair<char, std::uint16_t>> ccc{{'A', {11, 'c'}}};
    auto p = encodeString(ccc, "A");
    std::cout << "'" << p.second <<"'" << std::endl;

#else
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    // HACK: 'z' is the end character. 'z' is not present in the abc
    //input += "z";
    std::map<char, unsigned> data;
    for (char c : input) {
        ++data[c];
    }

    std::cout << "Letters and frequencies : " << std::endl;
    for (const auto& p : data) {
        std::cout << (int)p.first << ' ' << p.second << std::endl;
    }

    Node* root = createTree(data);
    //printTree(root);
    std::map<char, std::pair<char, std::uint16_t>> codes;
    generateCodes(root, codes);
    for (const auto& pair : codes) {
        std::cout << static_cast<int>(pair.first) << ": "
                  << pair.second.second << '/' << static_cast<int>(
                          pair.second.first)
                  << std::endl;
    }

    std::map<std::pair<char, std::uint16_t>, char> invCodes;
    for (const auto& c : codes) {
        invCodes[c.second] = c.first;
    }

    // for (const auto& c : invCodes) {
    //     std::cout << "{{" << (int)c.first.first << ", " << c.first.second
    //               << "}, " << c.second << "}" << std::endl;
    // }

#if 0 // only for debugging
    std::size_t start = 0;
    std::size_t length = 10;
    while (start + length < input.size()) {
        std::cout << "encoding string from " << start << std::endl;
        std::string s = input.substr(start, length);
        auto bs = encodeString(codes, s);
        std::string ds = decodeString(invCodes, bs.first, bs.second);
        if (ds != s) {
            std::cout << "data mismatch! start: " << start << " length: "
                      << length << std::endl;
            for (char c : bs.second) {
                std::bitset<8> bs = c;
                std::cout << bs << ' ';
            }
            std::cout << std::endl;
            for (char c : s) {
                std::bitset<8> bs = c;
                std::cout << bs << ' ';
            }
            std::cout << std::endl;
            for (char c : ds) {
                std::bitset<8> bs = c;
                std::cout << bs << ' ';
            }
            std::cout << std::endl;
        }
        start += length;
    }
#endif
    // To be able to stringify the tree two characters are used to represent the
    // empty parts of a tree and the
    //std::cout << "'" << toString(root) << "'" << std::endl;

    auto p = encodeString(codes, input);
    // for (char c : p.second) {
    //     std::bitset<8> bitset = c;
    //     std::cout << bitset;
    // }
    // std::cout << std::endl;
    //std::cout << '"' << p.second << '"' << ' ' << p.second.size() << std::endl;

    //std::cout << decodeString(toString(root), p.first, p.second);

    std::ofstream treeofs("dns_tree.txt");
    treeofs << toString(root);
    treeofs.close();
    std::ofstream dataofs("dns_data.txt");
    dataofs << p.second;
    dataofs.close();

    //    std::string re = decodeString(invCodes, p.first, p.second);
    std::string re = decodeString(toString(root), p.first, p.second);
    //std::cout << '"' << re << '"' << ' ' << (re == input)
    //          << std::endl;
    std::cout << "bits: " << p.first << std::endl;
    std::cout << (re == input) << ' ' << re.size() << std::endl;
    int index = 0;
    for (char c : input) {
        if (c != re[index]) {
            std::cout << "Found erroreous character: " << (int)c << " as "
                      << (int)re[index] << " at position: " << index
                      << ' ' << (int)re[index-1]
                      << std::endl;
        }
        ++index;
        if (index > 100) break;
    }
#endif
}
