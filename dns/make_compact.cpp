#include "lzw.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    std::ifstream t("dns.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    t.close();

    std::map<char, char> dict{{'A',0},{'C',1},{'G',2},{'T',3}};
    std::string compactStr;
    std::string::const_iterator it = str.cbegin();
    while (it != str.cend()) {
        compactStr.push_back((dict[*it++] << 6) + (dict[*it++] << 4) +
                (dict[*it++] << 2) + (dict[*it++]));
    }

    std::ofstream ofs("dns_compact.txt");
    ofs << compactStr;
    ofs.close();

    std::map<std::string, int> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary[std::string(1, i)] = i;
    }

    std::vector<int> compressed;
    compress(compactStr, std::back_inserter(compressed), dictionary);
    std::cout << compressed.size() << ' ' << dictionary.size() << std::endl;
}
