#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <chrono>
#include <assert.h>

int main() {
    using Clock = std::chrono::high_resolution_clock;
    constexpr auto Den = Clock::period::den;
    constexpr auto Num = Clock::period::num;
    auto start = Clock::now().time_since_epoch().count();

    std::size_t num;
    std::cin >> num;
    std::vector<std::string> strings;
    strings.reserve(num);
    while (std::cin.good()) {
        std::string s;
        std::getline(std::cin, s, '\n');
        if (!s.empty()) {
            strings.push_back(std::move(s));
        }
    }
    std::cerr << "read done\n";

    auto read_end = Clock::now().time_since_epoch().count();
    std::cerr << "Read took: " << (read_end - start) / double(Den) * Num << std::endl;

    assert(strings.size() == num);
    auto sort_start = Clock::now().time_since_epoch().count();
    std::sort(strings.begin(), strings.end());
    auto sort_end = Clock::now().time_since_epoch().count();
    std::cerr << "Sort took: " << (sort_end - sort_start) / double(Den) * Num << std::endl;
    std::copy(strings.begin(), strings.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
    auto write_end = Clock::now().time_since_epoch().count();
    std::cerr << "Write took: " << (write_end - sort_end) / double(Den) * Num << std::endl;
}
