//#include <cstdint>
//#include <iostream>
#include <cassert>
#include <cstring>
#include <limits>
#include <map>
#include <string>
#include <vector>

// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.
std::string lzwCompress(const std::string& uncompressed,
        std::map<std::string, std::uint16_t>& dictionary) {
    std::vector<std::uint16_t> result;
    // Build the dictionary.
    std::uint16_t dictSize = dictionary.size();
    // std::map<std::string,int> dictionary;
    // for (int i = 0; i < 256; i++)
    //     dictionary[std::string(1, i)] = i;

    std::string w;
    for (std::string::const_iterator it = uncompressed.begin();
         it != uncompressed.end(); ++it) {
        char c = *it;
        std::string wc = w + c;
        if (dictionary.count(wc))
            w = wc;
        else {
            //*result++ = dictionary[w];
            result.push_back(dictionary[w]);
            //std::cout << w << ":" << dictionary[w] << "/" << wc << ",";
           // Add wc to the dictionary.
            dictionary[wc] = dictSize++;
            assert(dictSize < std::numeric_limits<std::uint16_t>::max());
            w = std::string(1, c);
        }
    }

    // Output the code for w.
    if (!w.empty()) {
        result.push_back(dictionary[w]);
    }

    std::string output(sizeof(std::uint16_t)*result.size(), '=');
    std::memcpy(&*output.begin(), result.data(),
            result.size() * sizeof(std::uint16_t));
    return output;
}

// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
std::string lzwDecompress(std::string input,
        std::map<std::uint16_t, std::string> dictionary) {
    // Build the dictionary.
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
    return result;
}
