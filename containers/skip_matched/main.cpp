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

Result solve(char* actual, const char* desired, int size, int offset) {
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

    int max_value = 0;
    Reversal max_reversal{0, 0}; // Arbitrary
    const int N = size;
    for (int m = N; m > 0; --m) {
        std::string candidate(actual, actual + m);
        std::reverse(candidate.begin(), candidate.end());
        auto value = equalAtFront(&candidate[0], &desired[0], candidate.size());
        if (value > max_value) {
            max_reversal = {0, m}; // closed intervall needed
            max_value = value;
        }
    }
    assert(max_value != 0);

    std::reverse(&actual[std::get<0>(max_reversal)],
                 &actual[std::get<1>(max_reversal)]);
    result.push_back(
        {offset + skipped + std::get<0>(max_reversal),
         offset + skipped + std::get<1>(max_reversal) - 1 /*closed interval*/});

    auto rest = solve(&actual[max_value], &desired[max_value], N - max_value,
                      offset + skipped + max_value);
    for (const auto& r : rest) {
        result.push_back(r);
    }

    return result;
}

Result solve(std::string actual, const std::string desired) {
    return solve(const_cast<char*>(actual.data()), desired.data(),
                 actual.size(), 0);
}

void test1() {
    ASSERT(equalAtFront("aab", "aac", 3) == 2);
    ASSERT(equalAtFront("", "", 0) == 0);
    ASSERT(equalAtFront("a", "b", 0) == 0);
    ASSERT(equalAtFront("a", "a", 1) == 1);
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

