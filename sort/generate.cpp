#include <boost/lexical_cast.hpp>

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <assert.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Bad arguments.\n";
        return 1;
    }

    std::size_t num = boost::lexical_cast<std::size_t>(argv[1]);
    std::cout << num << '\n';

    std::mt19937 rng{std::random_device{}()};

    std::uniform_int_distribution<int> lengthDistribution{4, 64};
    std::uniform_int_distribution<char> valueDistribution{'a', 'z'};
    for (std::size_t i = 0; i < num; ++i) {
        int length = lengthDistribution(rng);
        for (int j = 0; j < length; ++j) {
            std::cout << valueDistribution(rng);
        }
        std::cout << '\n';
    }
}

