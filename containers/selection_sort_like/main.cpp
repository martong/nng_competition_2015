#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <cassert>
#include <algorithm>

#define ASSERT(CONDITION)                                                      \
    do                                                                         \
        if (!(CONDITION)) {                                                    \
            printf("Assertion failure %s:%d ASSERT(%s)\n", __FILE__, __LINE__, \
                   #CONDITION);                                                \
            abort();                                                           \
        }                                                                      \
    while (0)

/**
 * The basic idea is to do a modified selection sort.
 * Each and every exchange can be represented at most by two reversals.
 * Selection sort is O(n) for the number of exchanges.
 */

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

// Create a position mapping of the desired string.
// I.e "cabbc" --> {{'c', {0, 4}}, {'a', {1}}, {'b', {2, 3}}}
using Positions = std::deque<int>;
using PositionMap = std::unordered_map<char, Positions>;
PositionMap makePositionMap(const std::string& desired) {
    PositionMap pm;
    for (int i = 0; i < desired.size(); ++i) {
        pm[desired[i]].push_back(i);
    }
    return pm;
}

void test_makePositionMap() {
    {
        auto pm = makePositionMap("cab");
        ASSERT((pm == PositionMap{{'c', {0}}, {'a', {1}}, {'b', {2}}}));
    }
    {
        auto pm = makePositionMap("cabbc");
        ASSERT((pm == PositionMap{{'c', {0, 4}}, {'a', {1}}, {'b', {2, 3}}}));
    }
}

Result exchSolve(std::string actual, const std::string desired) {
    Result result;
    auto exch = [&result](std::string& a, int x, int y) {
        if (x == y) return;
        if (a[x] == a[y]) return;
        std::reverse(a.begin() + x, a.begin() + y + 1);
        result.emplace_back(x, y);
    };

    auto pm = makePositionMap(desired);
    // Modified selection sort
    const int N = actual.size();
    for (int i = 0; i < N; ++i) {
        int min = i;
        for (int j = i + 1; j < N; ++j) {
            // In selection sort, we'd update like this:
            // if (less(actual[j], actual[min])) { min = j; }
            // However, now we update based on the position map
            auto j_rank = pm[actual[j]].at(0);
            auto min_rank = pm[actual[min]].at(0);
            if (j_rank < min_rank) {
                min = j;
            }
        }
        exch(actual, i, min);
        // Actualize the position map
        pm[actual[i]].pop_front();
    }
    return result;
}

void test_exchSolve() {
    //{
        //auto er = exchSolve("abc", "cab");
        //ASSERT((er == Result{{0, 2}, {1, 2}}));
    //}
    //{
        //auto er = exchSolve("abccb", "cabbc");
        //ASSERT((er == Result{{0, 2}, {1, 2}, {3, 4}}));
    //}
}

int test() {
    test_makePositionMap();
    test_exchSolve();
    std::cout << "OK\n";
    return 0;
}

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
    } else
        std::cerr << "Unable to open file";

    auto result = exchSolve(actual, desired);
    std::cout << result;
    return 0;
}

