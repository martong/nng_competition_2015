#include <iostream>
#include <map>

int main() {
    std::map<char, int> map;
    char c;
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        map[c]++;
    }
    std::multimap<int, char> map2;

    for (const auto& element : map) {
        //std::cout << (int)element.first << ": " << element.second << "\n";
        map2.emplace(element.second, element.first);
    }
    for (const auto& element : map2) {
        std::cout << (int)element.second << ": " << element.first << "\n";
    }
    return 0;
}

