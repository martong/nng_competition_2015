#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <assert.h>
#include <string.h>

int main() {
    std::size_t num;
    std::cin >> num;

    std::vector<char> array;
    array.resize(num * 65);
    std::size_t i = 0;
    std::vector<const char*> vector;
    vector.reserve(num);
    while (std::cin.good()) {
        std::string s;
        std::getline(std::cin, s, '\n');
        if (!s.empty()) {
            strncpy(&array[i * 65], s.c_str(), 65);
            vector.push_back(&array[i * 65]);
        }
        ++i;
    }
    assert(vector.size() == num);

    std::cerr << "read done\n";

    std::sort(vector.begin(), vector.end(),
            [](const char* lhs, const char* rhs) {
                return strcmp(lhs, rhs) < 0;
            });
    std::copy(vector.begin(), vector.end(),
            std::ostream_iterator<const char*>(std::cout, "\n"));
}

