#include <iostream>

int main() {
    std::string input((std::istreambuf_iterator<char>(std::cin)),
            std::istreambuf_iterator<char>());

    unsigned count = 0;
    for (char c : input) {
        if (c == 0) {
            ++count;
        }
    }

    std::cout << "number of zero bytes: " << count << std::endl;
}
