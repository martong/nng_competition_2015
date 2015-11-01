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
    char ch = std::cin.get();
    static_cast<void>(ch);
    assert(ch == '\n');

    std::vector<char> array;
    array.resize(num * 65);
    std::vector<const char*> vector;
    vector.resize(num);
    std::size_t i = 0;
    std::size_t index = 0;
    vector[0] = &array[0];
    while (std::cin.get(array[index]).good()) {
        if (array[index] == '\n') {
            ++i;
            array[index] = '\0';
            index = i * 65;
            vector[i] = &array[index];
        } else {
            ++index;
        }
    }

    std::cerr << "read done\n";

    std::sort(vector.begin(), vector.end(),
            [](const char* lhs, const char* rhs) {
                return strcmp(lhs, rhs) < 0;
            });
    std::copy(vector.begin(), vector.end(),
            std::ostream_iterator<const char*>(std::cout, "\n"));
}

