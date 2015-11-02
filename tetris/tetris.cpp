#include "Array.hpp"
#include "Point.hpp"
#include "PointRange.hpp"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <vector>

using Table = Array<bool>;

std::ostream& operator<<(std::ostream& os, const Table& array) {
    Point p;
    for (p.y = 0; p.y < static_cast<int>(array.height()); ++p.y) {
        for (p.x = 0; p.x < static_cast<int>(array.width()); ++p.x) {
            os << (array[p] ? 'X' : ' ');
        }
        os << '\n';
    }
    return os;
}

void iterate(Table table, std::size_t n, Point p,
        std::vector<Table>& result);

void findNextIteration(const Table& table, std::size_t n,
        std::vector<Table>& result) {
    if (n == 0) {
        result.push_back(table);
        return;
    }

    for (Point p : arrayRange(table)) {
        if (table[p]) {
            if (!table[p + p10]) {
                iterate(table, n, p + p10, result);
            }
            if (!table[p + p01]) {
                iterate(table, n, p + p01, result);
            }
        }
    }
}

void iterate(Table table, std::size_t n, Point p,
        std::vector<Table>& result) {
    table[p] = true;
    table[p + p10] = true;
    findNextIteration(table, n - 1, result);
    table[p + p10] = false;
    table[p + p01] = true;
    findNextIteration(table, n - 1, result);
}

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong arguments.\n";
        return 1;
    }

    std::size_t numberOfTiles = boost::lexical_cast<std::size_t>(argv[1]);

    std::size_t size = numberOfTiles * 2;

    std::vector<Table> result;
    iterate(Table{size, size, false}, numberOfTiles, Point{0, 0}, result);

    std::cout << result.size() << ' ' << size << '\n';
    for (const auto& element : result) {
        std::cout << element;
    }
}
