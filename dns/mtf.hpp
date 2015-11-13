#ifndef DNS_MTF_HPP
#define DNS_MTF_HPP

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include <iostream>

//============================================================================//
namespace mtf {
//----------------------------------------------------------------------------//

// Instead of writing \0 bytes for consecutive bytes, value 255 is used to save
// space and allow

std::string encode(std::string data) {
    std::string output;
    std::vector<char> alphabet(256);
    for (int i = 0; i < 256; ++i) {
        alphabet[i] = i;
    }

    for (char c : data) {
        auto it = std::find(alphabet.begin(), alphabet.end(), c);
        std::size_t i = it - alphabet.begin(); // random access iterator
        //std::cerr << i << ' ' << alphabet.size() << std::endl;
        assert(it != alphabet.end());
        alphabet.erase(it);
        alphabet.push_back(c);
        output.append(1, 255-i);
    }

    return output;
}

std::string decode(std::string data) {
    std::string output;
    std::vector<char> alphabet(256);
    for (int i = 0; i < 256; ++i) {
        alphabet[i] = i;
    }

    for (unsigned char c : data) {
        char elem = alphabet[255-c];
        output.append(1, elem);
        alphabet.erase(alphabet.end() - 1 - c);
        alphabet.push_back(elem);
    }

    return output;
}

//----------------------------------------------------------------------------//
} // namespace mtf
//============================================================================//

#endif // DNS_MTF_HPP
