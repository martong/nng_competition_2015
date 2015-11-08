#include <iostream>
#include <random>

int main() {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<unsigned char> dist{0, 255};
    for (int i = 0; i < 20000; ++i) {
        std::cout << dist(rng);
    }
}
