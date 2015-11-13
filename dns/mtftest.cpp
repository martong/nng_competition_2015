#include "mtf.hpp"

#include <iostream>
#include <iterator>
#include <string>

int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    std::string encoded = mtf::encode(input);
    std::cerr << (input == mtf::decode(encoded)) << std::endl;
}
