#ifndef DNS_BWT_HPP
#define DNS_BWT_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

//============================================================================//
namespace dns {
//----------------------------------------------------------------------------//

std::string bwt(std::string data) {
    //data.push_back('Z'); // 'EOF' element
    std::vector<std::string> rotations{data.size()};
    rotations[0] = data;
    //std::cout << data << std::endl;
    for (std::size_t i = 1; i < data.size(); ++i) {
        std::string s = data;
        std::rotate(s.begin(), s.end() - i, s.end());
        // std::cout << s << std::endl;
        rotations[i] = s;
    }
    std::sort(rotations.begin(), rotations.end());
    std::string output;
    std::vector<std::string>::iterator indexIt;
    for (std::string s : rotations) {
        //std::cout << s << std::endl;
        output += *--s.end();
        if (s == data) {
            indexIt = std::find(rotations.begin(), rotations.end(), s);
        }
    }
    std::uint16_t index = (indexIt - rotations.begin());
    return std::string{""} + static_cast<char>(index)
                               + static_cast<char>(index>>8) + output;
}

std::string bwt2(std::string data) {
    //data.push_back('Z'); // 'EOF' element
    //data = "$" + data + "Z";
    std::vector<std::string::iterator> rotations{data.size()};
    std::string::iterator it = data.end();
    rotations[0] = data.begin();
    for (std::size_t i = 1; i < data.size(); ++i) {
        // std::cout << (std::string(it, data.end()) +
        //         std::string(data.begin(), it)) << std::endl;
        rotations[i] = --it;
    }
    std::sort(rotations.begin(), rotations.end(),
            [&data](std::string::iterator lhs,
                    std::string::iterator rhs) {
                std::string lhsString = std::string{lhs, data.end()}
                        + std::string{data.begin(), lhs};
                std::string rhsString = std::string{rhs, data.end()}
                        + std::string{data.begin(), rhs};
                        //std::cout << lhsString << ' ' << rhsString << ' '
                        //          << (lhsString < rhsString) << std::endl;
                return lhsString < rhsString;
            });
    // std::cout << "after sort..." << std::endl;
    std::string output;
    std::vector<std::string::iterator>::iterator indexIt =
        rotations.begin();
    for (std::string::iterator i : rotations) {
        if ((std::string{i, data.end()} + std::string{data.begin(), i})
                == data) {
            indexIt = std::find(rotations.begin(), rotations.end(), i);
            // std::cout << "found " << (indexIt - rotations.begin()) << std::endl;
        }
        // std::cout << (std::string{i, data.end()} +
        //         std::string{data.begin(), i}) << std::endl;
        output += (data.begin() == i) ? *--data.end() : *--i;
    }

    std::uint16_t index = indexIt - rotations.begin();
    //std::cerr << "encoding index: " << index <<  " size: " << output.size() << std::endl;
    return std::string{""} + static_cast<char>(index) + static_cast<char>(index>>8) +  output;
}

std::string inverseBwt2(std::string data) {

    std::map<unsigned char, int> sums;
    std::map<unsigned char, int> cumulativeSums;
    std::vector<int> precedingMatchingSymbols;
    std::uint16_t index = (std::uint16_t&)data[0];

    data = data.substr(2);
    //std::cerr << "decoded index: " << index << " size: " << data.size() << std::endl;

    for (const unsigned char& c : data) {
        precedingMatchingSymbols.push_back(sums[c]++);
    }

    int sum = 0;
    for (const auto& p : sums) {
        cumulativeSums[p.first] = sum;
        sum += p.second;
    }

    std::string output(data.size(), '=');
    //output[output.size() - 1] = data[index];
    int m = index;
    auto s = output.size();
    for (auto i = s-1; (i+s) >= s; --i) {
        output[i] = data[m];
        // std::cout << i << ' ' << output[i] << ' ' << output <<  ' '
        //           << m << ' ' << data[m] << std::endl;
        m = (precedingMatchingSymbols[m] + cumulativeSums[output[i]]);
    }

    return output;
}

std::string inverseBwt(std::string data) {
    std::vector<std::string> rotations{data.size()};
    for (std::size_t i = 0; i < data.size(); ++i) {
        // std::cout << i << ", ";
        // std::cout.flush();
        std::string::const_iterator it = data.begin();

        //std::cout << "inserting..." << std::endl;
        for (std::string& s : rotations) {
            s = (*it++) + s;
        }
        //std::cout << "sorting..." << std::endl;
        std::sort(rotations.begin(), rotations.end());
    }


    for (std::string& s : rotations) {
        if (s[s.size() - 1] == 'Z') {
            return s.substr(0, s.size() - 1);
        }
    }

    return "";
}

//----------------------------------------------------------------------------//
} // namespace dns
//============================================================================//

#endif // DNS_BWT_HPP
