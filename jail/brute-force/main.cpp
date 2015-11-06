#include <vector>
#include <iostream>
#include <fstream>

using Group = std::vector<int>;
using Groups = std::vector<Group>;
using Result = Groups;
using Indexes = std::vector<int>;

bool goodFit(const Group& g, int e) {
    for (int i = 0; i < g.size(); ++i) {
        for (int j = i + 1; j < g.size(); ++j) {
            int a = g[i];
            int b = g[j];
            if (a + b == e || a == b + e || b == a + e) {
                return false;
            }
        }
    }
    return true;
}

Groups solve(const Indexes& indexes) {
    Groups groups;
    for (int i : indexes) {
        bool fit = false;
        for (auto& g : groups) {
            if (goodFit(g, i)) {
                g.push_back(i);
                fit = true;
                break;
            }
        }
        // Add new group if not fit anywhere
        if (!fit) {
            groups.push_back({i});
        }
    }
    return groups;
}

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
    Indexes indexes;
    std::ifstream myfile(argv[1]);
    if (myfile.is_open()) {
        int count = 0;
        myfile >> count;
        for (int i = 0; i < count; ++i) {
            int index = 0;
            myfile >> index;
            indexes.push_back(index);
        }
    } else
        std::cerr << "Unable to open file";
    auto r = solve(indexes);
    std::cout << r;
}
