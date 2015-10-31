#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <assert.h>

int main() {
    std::vector<std::string> strings;

    std::size_t num;
    std::cin >> num;
    while (std::cin.good()) {
        std::string s;
        std::getline(std::cin, s, '\n');
        if (!s.empty()) {
            strings.push_back(std::move(s));
        }
    }
    std::cerr << strings.size() << '\n';
    assert(strings.size() == num);
    std::sort(strings.begin(), strings.end());
    std::copy(strings.begin(), strings.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}
