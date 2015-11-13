#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "wrong arguments" << std::endl;
    }

    std::string chars = argv[1];

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

    // for (const auto& pair : invData) {
    //     std::cout << static_cast<int>(pair.second) << ": " << pair.first
    //               <<std::endl;
    // }

    std::size_t index = 0;
    std::map<char, char> m;
    for (auto& it = --invData.end(); it != invData.begin(); --it) {
        if (index < chars.size()) {
            m[it->second] = chars[index++];
        } else {
            m[it->second] = it->second;
        }
    }

    for (char c : input) {
        std::cout << m[c];
    }
}
