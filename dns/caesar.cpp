#include <iostream>

int main() {
    char c;
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        std::cout << (char)(c - 74);
    }
    return 0;
}


