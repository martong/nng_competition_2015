#include "bwt.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::string str = "GAACTAAGGA";
    //std::ifstream t("dns.txt");
    //std::string str((std::istreambuf_iterator<char>(t)),
    //        std::istreambuf_iterator<char>());

    std::size_t index;
    std::string compressed;
    std::tie(index, compressed) = dns::bwt2(str);
    std::cout << index << ' ' << compressed << std::endl;
    //std::ofstream ofs("dns_bwt.txt");
    //ofs << compressed;
    std::cout << "decompressing..." << std::endl;
    std::string decompressed = dns::inverseBwt2(index, compressed);
    std::cout << decompressed << ' ' << (str == decompressed) << std::endl;

    // std::string c2 = dns::bwt2(str);
    // std::cout << (compressed == c2) << std::endl;
}

int main2() {
    std::map<std::string, int> dictionary{{"A",0},{"C",1},{"G",2},{"T",3}};
    std::ifstream t("dns.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
    std::string compressed = dns::bwt(str);
    //compress(str, std::back_inserter(compressed), dictionary);
    //auto key = townsend::algorithm::bwtEncode(compressed.begin(), compressed.end());
    std::cout << compressed.size() << ' ' << dictionary.size() << std::endl;
    std::ofstream ofs_bwt("dns_bwt.txt");
    ofs_bwt << compressed;
    ofs_bwt.close();

    //copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
    //std::cout << std::endl;
    //std::string decompressed = decompress(compressed.begin(), compressed.end(),
    //        {{0,"A"},{1,"C"},{2,"G"},{3,"T"}});
    //std::cout << decompressed << std::endl;
    //townsend::algorithm::bwtDecode(compressed, key);
    //std::cout << decompressed.size() << ' ' << str.size() << ' '<< (decompressed == str) << std::endl;

    std::ofstream ofs("dns_o.txt");
    ofs << compressed;
    ofs.close();

    return 0;
}
