#include "huffman.hpp"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main() {
    // IT DOES NOT WORK!!!
    int numberOfBits = 0;
    std::cin.read(reinterpret_cast<char*>(&numberOfBits), sizeof(numberOfBits));
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    std::map<char, unsigned> data;
    for (char c : input) {
        ++data[c];
    }

    Node* root = createTree(data);
    std::map<char, std::pair<char, std::uint16_t>> codes;
    generateCodes(root, codes);

    std::map<std::pair<char, std::uint16_t>, char> invCodes;
    for (const auto& c : codes) {
        invCodes[c.second] = c.first;
    }


    std::cout << decodeString(invCodes, numberOfBits, input);
}
