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
    std::map<unsigned char, std::pair<const char*, bool>> escapeSequences = {
        {'\a', {"\a", false}},
        {'\b', {"\b", false}},
        {'\f', {"\f", false}},
        {'\v', {"\v", false}},
        {'\n', {"\\n", false}},
        {'\r', {"\\r", false}},
        {'"', {"\\\"", false}},
        {'\\', {"\\\\", false}},
        //{'\0', {"\\0", true}},
    };
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        ++n;
        auto it = escapeSequences.find(c);
        if (it != escapeSequences.end()) {
            std::cout << it->second.first;
            wasNumSequence = it->second.second;
        } else if (wasNumSequence && c >= '0' && c <= '9') {
            std::cout << "\"\"" << c;
            wasNumSequence = false;
        } else {
            std::cout << c;
            wasNumSequence = false;
        }
    }
    std::cout << std::dec << R"(";
    for (std::size_t i = 0; i < )" << n << R"(; ++i) {
        std::cout << c[i];
    }
})";
    return 0;
}
