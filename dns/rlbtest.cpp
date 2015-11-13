#include "rlb.hpp"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    std::vector<int> encoded = rlb::encode(input);
    std::cerr << (input == rlb::decode(encoded)) << ' ' << std::endl;
}
