#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <cassert>

using Shift = std::vector<int>;
using Result = std::vector<Shift>;
using Indexes = std::vector<int>;

// both end closed intervall
using Interval = std::tuple<int, int>;
using Intervals = std::vector<Interval>;

// Duplicate indicates that we are running with duplicate numbers.
// This algorithm is not general.
// We exploit the fact that we have numbers from 1..n
// OR pair of numbers like 1,1...n,n.
Intervals partition(int n, bool duplicate) {
    if (n < 1) {
        return {};
    }
    if (duplicate) {
        if (n == 0) {
            return {};
        }
        if (n == 1) {
            return {{1, 1}};
        }
        if (n == 2) {
            return {{1, 1},{2, 2}};
        }
    }
    Intervals intervals;
    auto lower = std::ceil(n / 2.0);
    if (duplicate) {
        lower = lower + 1;
    }
    intervals.push_back({lower, n});
    auto rest = partition(lower - 1, duplicate);
    for (const auto& i : rest) {
        intervals.push_back(i);
    }
    return intervals;
}

Result solve(const Indexes& indexes) {
    int max = *std::max_element(indexes.begin(), indexes.end());

    // This is the duplicate indexes version
    bool duplicate =
        2 == std::count(indexes.begin(), indexes.begin() + 2, indexes.front());

    auto intervals = partition(max, duplicate);

    Result r;
    for (const auto& i : intervals) {
        auto size = std::get<1>(i) - std::get<0>(i) + 1;
        assert(size > 0);
        if (duplicate) {
            Shift s(size * 2);
            auto iota2 = [](auto first, auto last, auto value) {
                while (first != last) {
                    *first = value;
                    ++first;
                    if (first != last) {
                        *first = value;
                        ++first;
                    }
                    ++value;
                }
            };
            iota2(s.begin(), s.end(), std::get<0>(i));
            r.push_back(std::move(s));
        } else {
            Shift s(size);
            std::iota(s.begin(), s.end(), std::get<0>(i));
            r.push_back(std::move(s));
        }
    }
    return r;
}

std::ostream& operator<<(std::ostream& os, const Result& r) {
    std::cout << r.size() << "\n";
    for (const auto& s : r) {
        for (const auto& i : s) {
            os << i << " ";
        }
        os << "\n";
    }
    return os;
}

int main(int argc, char** argv) {
    Indexes indexes;
    std::ifstream myfile(argv[1]);
    if (myfile.is_open()) {
        int count = 0;
        myfile >> count;
        for (int i = 0; i < count; ++i) {
            int index = 0;
            myfile >> index;
            indexes.push_back(index);
        }
    } else
        std::cerr << "Unable to open file";
    auto r = solve(indexes);
    std::cout << r;
}
