#include <iostream>

int main() {
    char c;
    while (std::cin >> c) {
        if (c < 32) {
            std::cout << '\\' << std::oct << (int)c << std::dec;
        } else {
            std::cout << c;
        }
    }
}
