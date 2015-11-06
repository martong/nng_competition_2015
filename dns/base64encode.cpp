#include "base64.hpp"

#include <iostream>
#include <algorithm>

int main() {
    constexpr int bufferSize = 10000;
    char buffer[bufferSize];
    std::string s;
    while (std::cin.read(buffer, bufferSize).good()) {
        std::copy(buffer, buffer + std::cin.gcount(), std::back_inserter(s));
    }

    std::cout << base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()),
            s.size());
    return 0;
}
