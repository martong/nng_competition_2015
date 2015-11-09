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

    //for (const auto& p : data) {
    //std::cout << p.first << ' ' << p.second << std::endl;
    //}

    Node* root = createTree(data);
    std::string tree = toString(root);
    // int size = 0;
    // for (char c : tree) {
    //     if (c == 'e') {
    //         ++size;
    //     } else {
    //         if (size > 0) {
    //             std::cout << "+s(" << size << ")+";
    //         }
    //         std::cout << c;
    //     }
    // }
    std::cout << tree;
}
