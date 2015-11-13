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

    Node* root = createTree(data);
    std::map<char, std::pair<char, std::uint16_t>> codes;
    generateCodes(root, codes);
    std::string tree = mapToString(codes);
    std::cout << tree;
}
