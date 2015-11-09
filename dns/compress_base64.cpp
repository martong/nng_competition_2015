#include "base64.hpp"

#include <iostream>
#include <iterator>
#include <string>

int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    std::cout << base64_encode(
            reinterpret_cast<const unsigned char*>(input.c_str()),
            input.length());
}
