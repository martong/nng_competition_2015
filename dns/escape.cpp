#include <iostream>
#include <iomanip>
#include <map>

int main() {
    std::cout << "\"";
    unsigned char c;
    bool wasNumSequence = false;
    std::size_t n = 0;
    std::map<unsigned char, std::pair<const char*, bool>> escapeSequences = {
        //{'\a', {"\a", false}},
        //{'\b', {"\b", false}},
        //{'\f', {"\f", false}},
        //{'\t', {"\t", false}},
        //{'\v', {"\v", false}},
        {'\n', {"\\n", false}},
        {'\r', {"\\r", false}},
        {'"', {"\\\"", false}},
        {'\\', {"\\\\", false}},
        {'\0', {"\\0", true}},
        {'\032', {"\\32", true}},
        //{'\220', {"\220", true}},
        //{'\0xc2', {"\0xc2", true}},
    };
    for (auto e : escapeSequences) {
        std::cerr << (int)e.first << ' ' << e.second.first << ' ' << e.second.second << std::endl;
    }
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
    std::cout << std::dec << "\"";
    return 0;
}
