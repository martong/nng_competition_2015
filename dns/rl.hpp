#ifndef DNS_RL_HPP
#define DNS_RL_HPP

#include <cassert>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <sstream>

std::string rlEncode(int numberOfSymbols, std::string input) {
    std::string::size_type found = 0, nextFound = 0;
    std::ostringstream output;
//    std::cout << input.size() << std::endl;
    while (found < input.size()) {
        nextFound = input.find_first_not_of(input[found], found);
        if (nextFound == std::string::npos) {
            nextFound = input.size();
        }
        if (4 == numberOfSymbols) {
            std::map<char, int> dictionary{
                {'A',0},{'C',1},{'G',2},{'T',3}};
            char rl = dictionary[input[found]] << 6;
            while ((nextFound - found) > 0) {
                char increment = (nextFound != std::string::npos) ?
                    ((nextFound - found) > 63) ? 63 : nextFound - found
                            : input.size() - found;
//                std::cout << input[found] << ' ' << (int)increment << ' '
//                          << (int)rl <<  ' ' << found << std::endl;
                output << static_cast<char>(rl + increment);
                found += increment;
                //std::cout << found << ' ' << nextFound << std::endl;
            }
        } else if (256 == numberOfSymbols) {
            while ((nextFound - found) > 0) {
                unsigned char increment = ((nextFound - found) > 255) ? 255
                    : nextFound - found;
                output << input[found];
                output << increment;
                found += increment;
            }
        } else {
            throw 0; // lol
        }
        //nextFound = input.find_first_not_of(input[found], found);
    }

    return output.str();
}

std::string rlDecode(int numberOfSymbols, std::string input) {
    std::string output;
    for (char c : input) {
        if (4 == numberOfSymbols) {
            std::map<int, char> dictionary{
                {0,'A'},{1,'C'},{2,'G'},{3,'T'}};
            char amount = c & 0b00111111;
            char symbol = dictionary[(c & 0b11000000) >> 6];
            output.append(amount, symbol);
//            std::cout << std::hex << (int)((c & 0b11000000) >> 6) << std::dec << ' '
//                      << symbol << ' ' << (int)amount << std::endl;
        } else {
            throw 0; // lol
        }
    }
    return output;
}

#endif // DNS_RL_HPP
