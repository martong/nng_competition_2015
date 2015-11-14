#include "huffman.hpp"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main() {
   std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    std::map<char, unsigned> data;
    for (char c : input) {
        ++data[c];
    }

    // Node* root = createTree(data);
    // std::map<char, std::pair<char, std::uint16_t>> codes;
    // generateCodes(root, codes);

    //std::map<std::pair<char, std::uint16_t>, char> invCodes;
    // for (const auto& c : codes) {
    //     invCodes[c.second] = c.first;
    // }


    std::cout << decodeString(input);
}
