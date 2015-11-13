#ifndef DNS_RLB_HPP
#define DNS_RLB_HPP

#include <string>
#include <vector>

// Run length as in bzip
//============================================================================//
namespace rlb {
//----------------------------------------------------------------------------//

std::vector<int> encode(std::string input) {
    const int RUNA = 0;
    const int RUNB = 1;
    const int END = 258;
    std::vector<int> output;
    int run = 0;
    unsigned char lastChar = 0;
    for (unsigned char c : input) {
        if (c == lastChar) {
            ++run;
        } else {
            if (run > 0) {
                --run;
                while (true) {
                    if (run & 1) {
                        output.push_back(RUNB);
                    } else {
                        output.push_back(RUNA);
                    }
                    if (run < 2) {
                        break;
                    }
                    run = (unsigned)(run - 2) / 2;
                }
                run = 0;
            }
            output.push_back(static_cast<int>(c) + 1);
            lastChar = c;
        }
    }
    output.push_back(END);
    return output;
}

std::string decode(std::vector<int> input) {
    //const int RUNA = 0;
    const int RUNB = 1;
    const int END = 258;
    std::string output;
    int run = 0;
    int runPosition = 0;
    unsigned char lastChar = 0;
    for (int i : input) {
        if (i <= RUNB) {
            if (!runPosition) {
                runPosition = 1;
                run = 0;
            }
            run += (runPosition << i);
            runPosition <<= 1;
        } else {
            if (runPosition) {
                runPosition = 0;
                output.append(run, lastChar);
            }
            lastChar = i - 1;
            if (i != END) {
                output.append(1, i - 1);
            }
        }
    }
    return output;
}

//----------------------------------------------------------------------------//
} // namespace rlb
//============================================================================//

#endif // DNS_RLB_HPP
