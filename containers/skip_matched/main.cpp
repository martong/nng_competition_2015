#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ASSERT(CONDITION)                                                      \
    do                                                                         \
        if (!(CONDITION)) {                                                    \
            printf("Assertion failure %s:%d ASSERT(%s)\n", __FILE__, __LINE__, \
                   #CONDITION);                                                \
            abort();                                                           \
        }                                                                      \
    while (0)

using Reversal = std::tuple<int, int>;

using Reversals = std::vector<Reversal>;

using Result = std::vector<Reversal>;

std::ostream& operator<<(std::ostream& os, const Result& r) {
    os << r.size() << "\n";
    for (const auto& rev : r) {
        os << std::get<0>(rev) << " " << std::get<1>(rev) << "\n";
    }
    return os;
}

// Number of equal elements at front.
int equalAtFront(const char* a, const char* b, int size) {
    int i = 0;
    int match = 0;
    while (a[i] == b[i] && i <= size - 1) {
        ++i;
        ++match;
    }
    return match;
}

// Number of equal elements at back.
int equalAtBack(const char* a, const char* b, int size) {
    int i = size - 1;
    int match = 0;
    while (a[i] == b[i] && i >= 0) {
        --i;
        ++match;
    }
    return match;
}

// int equalAtBack2(const char* a, const char* b, int size) {
// int i = 0;
// int match = 0;
// while (a[size - 1 - i] == b[size - 1 - i] && i >= 0) {
//--i;
//++match;
//}
// return match;
//}

struct Bad {};

Result solveDown(char* actual, const char* desired, int size, int offset) {
    if (size <= 1) {
        return {};
    }

    Result result;

    int skipped = 0;
    while (*actual == *desired) {
        --actual;
        --desired;
        ++skipped;
    }
    if (skipped >= size) {
        return {};
    }

    int max_value = 0;
    int max_reversal = 0;
    const int N = size - skipped - 1;
    for (int m = N; m > 0; --m) {
        std::string candidate(actual - m, actual + 1);
        std::reverse(candidate.begin(), candidate.end());
        auto value =
            equalAtBack(&candidate.front(), &desired[-m], candidate.size());
        if (value > max_value) {
            max_reversal = m;
            max_value = value;
        }
    }
    if (max_value == 0) {
        throw Bad{};
    }

    std::reverse(&actual[-max_reversal], &actual[1]);
    result.push_back({offset - skipped - max_reversal,
                      offset - skipped /*closed interval*/});

    auto rest = solveDown(&actual[-max_value], &desired[-max_value],
                          N - max_value + 1, offset - skipped - max_value);
    for (const auto& r : rest) {
        result.push_back(r);
    }

    return result;
}

Result solveUp(char* actual, const char* desired, int size, int offset) {
    if (size <= 1) {
        return {};
    }

    Result result;

    int skipped = 0;
    while (*actual == *desired) {
        ++actual;
        ++desired;
        ++skipped;
    }
    if (skipped >= size) {
        return {};
    }

    int max_value = 0;
    Reversal max_reversal{0, 0}; // Arbitrary
    const int N = size - skipped;
    for (int m = N; m > 0; --m) {
        std::string candidate(actual, actual + m);
        std::reverse(candidate.begin(), candidate.end());
        auto value = equalAtFront(&candidate[0], &desired[0], candidate.size());
        if (value > max_value) {
            max_reversal = {0, m};
            max_value = value;
        }
    }
    if (max_value == 0) {
        throw Bad{};
    }

    std::reverse(&actual[std::get<0>(max_reversal)],
                 &actual[std::get<1>(max_reversal)]);
    result.push_back(
        {offset + skipped + std::get<0>(max_reversal),
         offset + skipped + std::get<1>(max_reversal) - 1 /*closed interval*/});

    auto rest = solveUp(&actual[max_value], &desired[max_value], N - max_value,
                        offset + skipped + max_value);
    for (const auto& r : rest) {
        result.push_back(r);
    }

    return result;
}

Result solve(const std::string& actual_, const std::string& desired) {
    assert(actual_.size() == desired.size());
    auto size = actual_.size();

    auto min = 2000;
    Result bestResult;
    for (int i = 0; i < size + 1; ++i) {
        // for (int i = 0; i < size; ++i) {
        try {
            std::string actual{actual_};
            Result result;
            Result rDown = solveDown(const_cast<char*>(actual.data() + i - 1),
                                     desired.data() + i - 1, i, i - 1);
            Result rUp = solveUp(const_cast<char*>(actual.data() + i),
                                 desired.data() + i, size - i, i);
            for (const auto& r : rUp) {
                result.push_back(r);
            }
            for (const auto& r : rDown) {
                result.push_back(r);
            }
            if (result.size() < min) {
                std::cerr << "---" << i << "------------\n";
                //std::cerr << result;
                min = result.size();
                bestResult = result;
            }
        } catch (Bad& e) {
        }
    }
    return bestResult;
}

void test1() {
    ASSERT(equalAtFront("aab", "aac", 3) == 2);
    ASSERT(equalAtFront("", "", 0) == 0);
    ASSERT(equalAtFront("a", "b", 1) == 0);
    ASSERT(equalAtFront("a", "a", 1) == 1);

    ASSERT(equalAtBack("baa", "caa", 3) == 2);
    ASSERT(equalAtBack("", "", 0) == 0);
    ASSERT(equalAtBack("a", "b", 1) == 0);
    ASSERT(equalAtBack("a", "a", 1) == 1);
}

int t() {
    // int main() {
    test1();
    return 0;
}

// int t(int argc, char** argv) {
int main(int argc, char** argv) {
    std::string actual, desired;
    std::ifstream myfile(argv[1]);
    if (myfile.is_open()) {
        getline(myfile, actual);
        if (!myfile) {
            std::cerr << "Error reading actual\n";
        }
        getline(myfile, desired);
        if (!myfile) {
            std::cerr << "Error reading desired\n";
        }
        myfile.close();
    } else {
        std::cerr << "Unable to open file\n";
        exit(1);
    }

    auto result = solve(actual, desired);
    std::cout << result;
    return 0;
}

