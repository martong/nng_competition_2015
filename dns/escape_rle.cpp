#include <iostream>
#include <iomanip>
#include <map>
#include <cstring>
#include <boost/lexical_cast.hpp>

std::map<char, std::pair<int, int>> overhead;
int overheadNumSequence = 0;
int winNum = 0;
int winAmount = 0;

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
    if (run.size() > 7 && run[0] == rleChar) {
        std::cout << "\" N(" << run.size() << ")\"";
        ++winNum;
        winAmount += run.size() - 7;
    } else {
        for (char c : run) {
            auto it = escapeSequences.find(c);
            if (it != escapeSequences.end()) {
                std::cout << it->second.first;
                wasNumSequence = it->second.second;
                auto& o = overhead[c];
                ++o.first;
                o.second += std::strlen(it->second.first);
            } else if (wasNumSequence && c >= '0' && c <= '9') {
                std::cout << "\"\"" << c;
                wasNumSequence = false;
                overheadNumSequence += 2;
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
    std::cerr << "Overhead:\n";
    for (const auto& element : overhead) {
        std::cerr << (int)element.first << ": " << element.second.first <<
                " (" << element.second.second << ")\n";
    }
    std::cerr << "Numeric overhead " << overheadNumSequence << "\n";
    std::cerr << "Win " << winNum << "(" << winAmount << ")" << "\n";
    return 0;
}
