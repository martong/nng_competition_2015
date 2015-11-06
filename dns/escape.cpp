#include <iostream>
#include <iomanip>
#include <map>

int main() {
    std::cout << R"(#include <iostream>
int main() {
    unsigned char c[] = ")";
    unsigned char c;
    bool wasNumSequence = false;
    std::size_t n = 0;
    std::map<unsigned char, char> escapeSequences = {
        {'\a', 'a'},
        {'\b', 'b'},
        {'\f', 'f'},
        {'\n', 'n'},
        {'\t', 't'},
        {'\v', 'v'},
        {'\a', 'a'},
        {'\\', '\\'},
        {'"', '"'},
    };
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        ++n;
        auto it = escapeSequences.find(c);
        if (it != escapeSequences.end()) {
            std::cout << '\\' << it->second;
            wasNumSequence = false;
        } else {
            if (c < 0x10) {
                std::cout << "\\" << std::oct << (int)c;
                wasNumSequence = true;
            } else if (wasNumSequence && c >= '0' && c <= '9') {
                std::cout << "\"\"" << c;
                wasNumSequence = false;
            } else {
                std::cout << c;
                wasNumSequence = false;
            }
        }
    }
    std::cout << std::dec << R"(";
    for (std::size_t i = 0; i < )" << n << R"(; ++i) {
        std::cout << c[i];
    }
})";
    return 0;
}
