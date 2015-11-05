#include "lzw.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::map<std::string, std::uint16_t> dictionary{{"A",0},{"C",1},{"G",2},{"T",3}};
    std::ifstream t("dns.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    //std::string str = "AAACCGGTTGGCC";
    //std::vector<int> compressed;
    std::string compressed = lzwCompress(str, dictionary);
    std::cout << compressed.size() << ' ' << dictionary.size() << std::endl;
    //copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
    //std::cout << std::endl;
    std::string decompressed = lzwDecompress(compressed,
            {{0,"A"},{1,"C"},{2,"G"},{3,"T"}});
    //std::cout << decompressed << std::endl;
    std::cout << decompressed.size() << ' ' << str.size() << ' '<< (decompressed == str) << std::endl;
    //std::cout << "'" <<  decompressed  << "' '" << str << "'" << std::endl;
    std::ofstream ofs("dns_o.txt");
    ofs << decompressed;
    ofs.close();

    return 0;
}
