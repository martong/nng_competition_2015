#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
#include <set>
#include <tuple>
#include <cassert>

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
using Exch = std::tuple<int, int>;

using PalindromInBetween = std::set<Exch>;

// Transform an exchange to at most two reversals.
using Reversals = std::vector<Reversal>;
Reversals map(const Exch& e, const PalindromInBetween& palindromInbetween) {
    int x = std::get<0>(e);
    int y = std::get<1>(e);
    assert(x <= y);
    if (x == y) return {};
    if (x >= y - 2) return {{x, y}};
    if (palindromInbetween.count(e)) return {{x, y}};
    Reversals rev;
    rev.push_back({x, y});
    rev.push_back({x + 1, y - 1});
    return rev;
}

using Result = std::vector<Reversal>;
using ExchResult = std::vector<Exch>;
// Transform all the exchanges to reversals
Result map(const ExchResult& er, const PalindromInBetween& palindromInbetween) {
    Result result;
    for (const auto& exch : er) {
        auto reversals = map(exch, palindromInbetween);
        for (const auto& reversal : reversals) {
            result.push_back(reversal);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Result& r) {
    os << r.size() << "\n";
    for (const auto& rev : r) {
        os << std::get<0>(rev) << " " << std::get<1>(rev) << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const PalindromInBetween& ps) {
    os << ps.size() << "\n";
    for (const auto& p : ps) {
        os << std::get<0>(p) << " " << std::get<1>(p) << "\n";
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

// Returns true if [b, e) is a palindrom in a.
bool palindrom(const std::string& a, int b, int e) {
    assert(b <= e);
    int N = e - b;
    for (int i = b; i < b + N / 2; ++i) {
        if (a[i] != a[e - (i - b) - 1]) return false;
    }
    //std::cout << "Palindrom " << b << " " << e << "\n";
    return true;
};

void test_palindrom() {
    ASSERT(palindrom("a", 0, 1));
    ASSERT(palindrom("aa", 0, 2));
    ASSERT(palindrom("aaa", 0, 3));
    ASSERT(palindrom("aba", 0, 3));
    ASSERT(palindrom("abba", 0, 4));
    ASSERT(palindrom("abbba", 0, 5));
    ASSERT(palindrom("xiabbajy", 2, 6));

    ASSERT(!palindrom("ab", 0, 2));
    ASSERT(!palindrom("abab", 0, 4));
}

std::tuple<ExchResult, PalindromInBetween> exchSolve(
    std::string actual, const std::string& desired) {

    ExchResult result;
    PalindromInBetween palindromInbetween;

    auto exch = [&result, &palindromInbetween](std::string& a, int x, int y) {
        if (x == y) return;

        if (palindrom(a, x + 1, y)) {
            palindromInbetween.insert(Exch{x, y});
        }

        std::swap(a[x], a[y]);
        //std::cout << "exch " << x << "," << y << std::endl;
        result.push_back(Exch{x, y});
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
    return {result, palindromInbetween};
}

void test_exchSolve() {
    {
        auto er = std::get<0>(exchSolve("abc", "cab"));
        ASSERT((er == ExchResult{{0, 2}, {1, 2}}));
    }
    {
        auto er = std::get<0>(exchSolve("abccb", "cabbc"));
        ASSERT((er == ExchResult{{0, 2}, {1, 2}, {3, 4}}));
    }
    {
        PalindromInBetween p;
        ExchResult r;
        std::tie(r, p) = exchSolve("xiabbajy", "xjabbaiy");
        ASSERT((r == ExchResult{{1, 6}}));
        ASSERT((p == PalindromInBetween{{1, 6}}));
    }
}

int test() {
    test_makePositionMap();
    test_palindrom();
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

    PalindromInBetween p;
    ExchResult r;
    std::tie(r, p) = exchSolve(actual, desired);
    auto result = map(r, p);
    std::cout << result;
    //std::cout << p;
    return 0;
}
