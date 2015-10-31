#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using Reversal = std::tuple<int, int>;
using Reversals = std::vector<Reversal>;

int main(int argc, char** argv) {
    std::string actual, desired;
    std::ifstream taskfile(argv[1]);
    if (taskfile.is_open()) {
        getline(taskfile, actual);
        if (!taskfile) {
            std::cerr << "Error reading actual\n";
        }
        getline(taskfile, desired);
        if (!taskfile) {
            std::cerr << "Error reading desired\n";
        }
        taskfile.close();
    } else
        std::cerr << "Unable to open file";

    Reversals reversals;
    std::ifstream solutionfile(argv[2]);
    if (solutionfile.is_open()) {
        int count;
        if (!solutionfile.eof()) {
            solutionfile >> count;
            //std::cout << count << "\n";
        }
        while (!solutionfile.eof() && count-- > 0) {
            int x, y;
            solutionfile >> x >> y;
            reversals.emplace_back(x, y);
            //std::cout << x << " " << y << "\n";
        }
    } else
        std::cerr << "Unable to open file";

    std::cout << reversals.size() << std::endl;
    for (const auto& reversal: reversals) {
        int x = std::get<0>(reversal);
        int y = std::get<1>(reversal);
        assert(y < actual.size());
        std::reverse(actual.begin() + x, actual.begin() + y + 1);
    }
    if (actual == desired) {
        std::cout << "OK\n";
        return 0;
    } else {
        std::cout << actual << "\n";
        std::cout << desired << "\n";
    }
    return 1;
}
