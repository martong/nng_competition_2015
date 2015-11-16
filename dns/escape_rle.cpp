#include <iostream>
#include <iomanip>
#include <map>
#include <boost/lexical_cast.hpp>

void finishRun(char rleChar, const std::string& run) {
    static const std::map<unsigned char, std::pair<const char*, bool>>
            escapeSequences = {
        {'\n', {"\\n", false}},
        {'\r', {"\\r", false}},
        {'"', {"\\\"", false}},
        {'\\', {"\\\\", false}},
        {'\0', {"\"+E(1,0)+\"", false}},
        {'\032', {"\\32", true}},
    };
    static bool wasNumSequence = false;
    if (run.size() > 8 && run[0] == rleChar) {
        std::cout << "\" N(" << run.size() << ")\"";
    } else {
        for (char c : run) {
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
    }
}

int main(int, char* argv[]) {
    char rleChar = boost::lexical_cast<int>(argv[1]);
    std::cout << "\"";
    char c;
    std::string run;
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        if (!run.empty() && run[0] != c) {
            finishRun(rleChar, run);
            run.clear();
        }
        run.push_back(c);
    }
    finishRun(rleChar, run);
    std::cout << std::dec << "\"";
    return 0;
}
