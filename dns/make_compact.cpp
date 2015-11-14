#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    std::string str((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());

    std::map<char, char> dict{{'A',0},{'C',1},{'G',2},{'T',3}};
    std::string compactStr;
    std::string::const_iterator it = str.cbegin();
    while (it != str.cend()) {
        compactStr.push_back((dict[*it++] << 6) + (dict[*it++] << 4) +
                (dict[*it++] << 2) + (dict[*it++]));
    }

    std::cout << compactStr;
}
