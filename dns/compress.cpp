//#include "lzw.hpp"
#include "rl.hpp"
#include "rlb.hpp"
#include "compact.hpp"
#include "bwt.hpp"
#include "mtf.hpp"
#include "huffman.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main(int argc, char* argv[]) {
    //int index = -1;
    //std::string data = "AAGGTTTTTTTTTGTGACCACGTCCCCATCAGACCATAGGATACATACAAGTTC";
    // std::ifstream t("dns.txt");
    // std::string data((std::istreambuf_iterator<char>(t)),
    //         std::istreambuf_iterator<char>());
    // t.close();
    std::string data((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());

    //std::map<std::string, std::uint16_t> dictionary{{"A",0},{"C",1},{"G",2},{"T",3}};

    std::string outputFileName = "dns";
    for (int i = 1; i < argc; ++i) {
        // if (std::string{"lzw"} == argv[i]) {
        //     data = lzwCompress(data, dictionary);
        //     outputFileName += "_lzw";
        // } else if (std::string{"c4"} == argv[i]) {
        //     data = cCompress4(data);
        //     outputFileName += "_c4";
        //     dictionary.clear();
        //     for (std::uint16_t i = 0; i < 256; ++i) {
        //         dictionary[std::string(1, i)] = i;
        //     }
        // } else if (std::string{"c2"} == argv[i]) {
        //     data = cCompress2(data);
        //     outputFileName += "_c2";
        // } else if (std::string{"bwt"} == argv[i]) {
        //     std::tie(index, data) = dns::bwt2(data);
        //     outputFileName += "_bwt";
        // } else if (std::string{"rl"} == argv[i]) {
        //     data = rlEncode(dictionary.size(), data);
        //     outputFileName += "_rl";
        //     for (std::uint16_t i = 0; i < 256; ++i) {
        //         dictionary[std::string(1, i)] = i;
        //     }
        // } else {
        //     std::cerr << "unknown option: " << argv[i] << std::endl;
        // }
        if (std::string{"rlb"} == argv[i]) {
            data = rlb::encodeStr(data);
            outputFileName += "_rlb";
        } else if (std::string{"rl"} == argv[i]) {
            data = rlEncode(256, data);
            outputFileName += "_rl";
        } else if (std::string{"bwt"} == argv[i]) {
            data = dns::bwt2(data);
            outputFileName += "_bwt";
        } else if (std::string{"mtf"} == argv[i]) {
            data =  mtf::encode(data);
            outputFileName += "_mtf";
        } else if (std::string{"huff"} == argv[i]) {
            data = encodeString(data);
            outputFileName += "_huff";
        }
    }

    outputFileName += ".txt";
    std::ofstream ofs(outputFileName);
    ofs << data;
    ofs.close();
}
