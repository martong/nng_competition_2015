#include "bwt.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::string str((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());

    std::string compressed = dns::bwt(str);
    //std::cout << index << ' ' << compressed << std::endl;
    //std::ofstream ofs("dns_bwt.txt");
    //ofs << compressed;
    //std::cout << compressed << ' ' << (int)compressed[0] << ' ' << (int) compressed[1] << std::endl;
    //std::cout << "decompressing..." << std::endl;
    std::string decompressed = dns::inverseBwt2(compressed);
    std::cout << (str == decompressed) << std::endl;
    //std::cout << decompressed << std::endl;

    if (str != decompressed) {
        int errors = 0;
        std::size_t start = 0, size = 10;
        while (start < str.size() && errors < 3) {
            std::string s = str.substr(start, size);
            std::string res = dns::inverseBwt2(dns::bwt(s));
            if (s != res) {
                std::cerr << "start: " << start << " size: " << size << std::endl;
                std::cerr << s << std::endl;
                std::cerr << "Does not match with"<<std::endl;
                std::cerr << res << std::endl;
                ++errors;
            }
            start += size;
        }
    }

    // std::string c2 = dns::bwt2(str);
    // std::cout << (compressed == c2) << std::endl;
}
