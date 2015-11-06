#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    std::map<char, int> data;
    for (char c : input) {
        ++data[c];
    }

    std::map<int, char> invData;
    for (const auto& pair : data) {
        invData[pair.second] = pair.first;
        //std::cout << static_cast<int>(pair.first) << ": " << pair.second
        //          << std::endl;
    }

    for (const auto& pair : invData) {
        std::cout << static_cast<int>(pair.second) << ": " << pair.first
                  <<std::endl;
    }

    std::cout << "The size of ABC: " << data.size() << std::endl;
}
