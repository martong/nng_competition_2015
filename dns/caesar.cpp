#include <iostream>
#include <boost/lexical_cast.hpp>

int main(int, char* argv[]) {
    char c;
    int i = boost::lexical_cast<int>(argv[1]);
    while (std::cin.get(reinterpret_cast<char&>(c)).good()) {
        std::cout << (char)(c - i);
    }
    return 0;
}


