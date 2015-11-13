#include <iostream>
#include <iomanip>
#include <map>

int main() {
    std::cout << R"(#include <iostream>
#include <string>
#define E(i) +std::string(i,'e')+
int main() {
    std::string c = ")";
    unsigned char c;
    std::size_t n = 0;

    int i = 0;
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        ++n;
        if (c == 'e') {
            ++i;
        } else if (i > 6) {
            std::cout << '"'<< "E(" << i << ")\"" << c;
            i = 0;
        } else if (i > 0) {
            std::cout << std::string(i, 'e') << c;
            i = 0;
        } else {
            std::cout << c;
        }
    }
    std::cout << std::dec << R"(";
    for (std::size_t i = 0; i < )" << n << R"(; ++i) {
        std::cout << c[i];
    }
})";
    return 0;
}
