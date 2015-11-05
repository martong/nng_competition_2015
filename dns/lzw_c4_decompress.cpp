#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

int main() {
    std::ifstream t("dns.txt");
    std::string original((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    t.close();

    std::ifstream inputT("dns_c4_lzw.txt");
    std::string input((std::istreambuf_iterator<char>(inputT)),
            std::istreambuf_iterator<char>());
    inputT.close();
    std::map<std::uint16_t, std::string> dictionary;
    for (std::uint16_t i = 0; i < 256; ++i) {
        dictionary[i] = std::string(1, i);
    }

    // LZW
    std::uint16_t dictSize = dictionary.size();
    // std::map<int,std::string> dictionary;
    // for (int i = 0; i < 256; i++)
    //     dictionary[i] = std::string(1, i);
    std::vector<std::uint16_t> data;
    data.resize(input.size() / sizeof(std::uint16_t));
    std::memcpy(data.data(), input.data(), input.size());
    std::vector<std::uint16_t>::iterator begin = data.begin(),
        end = data.end();

    std::string w = dictionary[*begin++];
    std::string result = w;
    std::string entry;
    for ( ; begin != end; begin++) {
        std::uint16_t k = *begin;
        if (dictionary.count(k)) {
            entry = dictionary[k];
        } else if (k == dictSize) {;
            entry = w + w[0];
        } else {
            //std::cout << k << " -> " << dictSize << std::endl;
            throw "Bad compressed k";
        }
        //std::cout << k << ":" << entry << "/" << (w+entry[0]) << ", ";
        result += entry;

        // Add w+entry[0] to the dictionary.
        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }
    // C4
    std::map<char, char> dict{{0,'A'},{1,'C'},{2,'G'},{3,'T'}};
    std::string output;
    for (char c : result) {
        // int a1 = dict[(char)((c & 0b11000000) >> 6)];
        // int a2 = dict[(char)((c & 0b00110000) >> 4)];
        // int a3 = dict[(char)((c & 0b00001100) >> 2)];
        // int a4 = dict[(char)((c & 0b00000011))];
        // std::cout << a1 << ' ' << a2 << ' ' << a3 << ' ' << a4 << std::endl;
        output.append(1, dict[(char)((c & 0b11000000) >> 6)]);
        output.append(1, dict[(char)((c & 0b00110000) >> 4)]);
        output.append(1, dict[(char)((c & 0b00001100) >> 2)]);
        output.append(1, dict[(char)((c & 0b00000011))]);
    }

    std::cout << (original == output) << std::endl;

    std::ofstream ofs("dns_back.txt");
    ofs << output;
    ofs.close();
}
