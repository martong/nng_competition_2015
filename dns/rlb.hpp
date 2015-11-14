#ifndef DNS_RLB_HPP
#define DNS_RLB_HPP

#include <cassert>
#include <string>
#include <vector>

#include <iostream>

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
    int runPosition = 1;
    unsigned char lastChar = 0;
    for (int i : input) {
        if (i <= RUNB) {
            run += (runPosition << i);
            runPosition <<= 1;
        } else {
            if (runPosition > 1) {
                runPosition = 1;
                output.append(run, lastChar);
                run = 0;
            }
            lastChar = i - 1;
            if (i != END) {
                output.append(1, i - 1);
            }
        }
    }
    return output;
}

std::string encodeStr(std::string input) {
    int needsMore = 3, hasMore = 0;
    int RUNA = -1, RUNB = -1, END = -1;
    // Find 3 unused characters if possible
    while (needsMore && hasMore < 256) {
        std::size_t i = input.find(hasMore++);
        if (i == std::string::npos && needsMore == 3) {
            RUNA = hasMore;
            --needsMore;
        } else if (i == std::string::npos && needsMore == 2) {
            RUNB = hasMore;
            --needsMore;
        } else if (i == std::string::npos && needsMore == 1) {
            END = hasMore;
            --needsMore;
        } else {
            assert(needsMore > 0);
        }
        ++hasMore;
    }
    assert(needsMore == 0);
    std::cerr << "RUNA: " << static_cast<int>(RUNA) << " RUNB: "
              << static_cast<int>(RUNB) << " END: " << static_cast<int>(END)
              << std::endl;
//    const int RUNA = 0;
//    const int RUNB = 1;
//    const int END = 258;
    std::string output;
    output.append(1, RUNA); output.append(1, RUNB); output.append(1, END);
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
            output.push_back(static_cast<int>(c));
            lastChar = c;
        }
    }
    output.push_back(END);
    return output;
}

std::string decodeStr(std::string input) {
    const int RUNA = input[0];
    const int RUNB = input[1];
    const int END = input[2];
    std::string output;
    int run = 0;
    int runPosition = 1;
    unsigned char lastChar = 0;
    for (int i : input.substr(3)) {
        if (i == RUNA || i == RUNB) {
            run += (runPosition << ((i == RUNA) ? 0 : 1));
            runPosition <<= 1;
        } else {
            if (runPosition > 1) {
                runPosition = 1;
                output.append(run, lastChar);
                run = 0;
            }
            lastChar = i;
            if (i != END) {
                output.append(1, i);
            }
        }
    }
    return output;
}


//----------------------------------------------------------------------------//
} // namespace rlb
//============================================================================//

#endif // DNS_RLB_HPP
