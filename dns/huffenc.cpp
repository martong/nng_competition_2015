#include "huffman.hpp"

#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    //std::map<char, unsigned> data;
    //for (char c : input) {
    //    ++data[c];
    //}

    //for (const auto& p : data) {
    //std::cout << p.first << ' ' << p.second << std::endl;
    //}

    //Node* root = createTree(data);
    //printTree(root);
    //std::map<char, std::pair<char, std::uint16_t>> codes;
    //generateCodes(root, codes);

    std::string encData = encodeString(input);
    // int digits = encData.first > 0 ?
    //     (int) log10 ((double) encData.first) + 1 : 1;
    // std::cout.write(reinterpret_cast<char*>(&encData.first),
    //         sizeof(encData.first));
    std::cout << encData;
}
