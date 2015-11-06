#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());
    std::map<std::size_t, std::size_t> matchMap;
    std::size_t matches = 0;
    std::size_t end = input.size() / 2;
    while (end > 5) {
        std::string sub = input.substr(0, end);
        std::size_t found = 0;
        do {
            found = input.find(sub, end + found);
            if (found != std::string::npos) {
                //std::cout << "A match is found at: " << found << " length: "
                //          << end << std::endl;
                ++matches;
                ++matchMap[end];
            }
        } while (found != std::string::npos);
        --end;
    }
    std::cout << "Found " << matches << " matches" << std::endl;
    for (const auto& pair : matchMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
