#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using Shift = std::vector<int>;
using Result = std::vector<Shift>;

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
    std::ifstream solutionfile(argv[1]);
    Result result;
    if (solutionfile.is_open()) {
        int count;
        if (!solutionfile.eof()) {
            std::string line;
            getline(solutionfile, line);
            std::stringstream ss(line);
            ss >> count;
        }
        while (!solutionfile.eof() && count-- > 0) {
            std::string line;
            getline(solutionfile, line);
            std::stringstream ss(line);
            Shift s;
            int x;
            while (ss >> x) {
                s.push_back(x);
            }
            result.push_back(std::move(s));
        }
    } else
        std::cerr << "Unable to open file";

    //std::cout << result;

    auto checkShiftIsGood = [](const Shift& s) {
        bool result = true;
        for (int i = 0; i < s.size(); ++i) {
            for (int j = i + 1; j < s.size(); ++j) {
                for (int k = j + 1; k < s.size(); ++k) {
                    bool check = s[i] == s[k] + s[j] || s[k] == s[i] + s[j] ||
                                 s[j] == s[k] + s[i];
                    if (check) {
                        std::cerr << s[i] << " " << s[j] << " " << s[k] << "\n";
                        result = false;
                    }
                }
            }
        }
        return true;
    };

    for (const auto& s : result) {
        if (!checkShiftIsGood(s)) return 1;
    }
    return 0;
}
