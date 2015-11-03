#include "Array.hpp"
#include "Point.hpp"
#include "PointRange.hpp"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <vector>

using Table = Array<bool>;
using Tables = std::vector<Table>;

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

void iterate(Table table, std::size_t n, Point p, Tables& result);

void nextIteration(const Table& table, std::size_t n, Point p, Tables& result) {
    if (!table[p]) {
        iterate(table, n, p, result);
    }
}

void findNextIteration(const Table& table, std::size_t n, Tables& result) {
    if (n == 0) {
        result.push_back(table);
        return;
    }

    for (Point p : arrayRange(table)) {
        if (table[p]) {
            nextIteration(table, n, p + p10, result);
            nextIteration(table, n, p - p10, result);
            nextIteration(table, n, p + p01, result);
            nextIteration(table, n, p - p01, result);
        }
    }
}

void iterateDirection(Table& table, std::size_t n, Point p, Tables& result) {
    if (!table[p]) {
        table[p] = true;
        findNextIteration(table, n - 1, result);
        table[p] = false;
    }
}

void iterate(Table table, std::size_t n, Point p, Tables& result) {
    table[p] = true;
    iterateDirection(table, n, p + p10, result);
    iterateDirection(table, n, p - p10, result);
    iterateDirection(table, n, p + p01, result);
    iterateDirection(table, n, p - p01, result);
}

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "Wrong arguments.\n";
        return 1;
    }

    std::size_t numberOfTiles = boost::lexical_cast<std::size_t>(argv[1]);

    std::size_t size = numberOfTiles * 4;
    int middle = numberOfTiles * 2;

    Tables result;
    iterate(Table{size, size, false}, numberOfTiles, Point{middle, middle},
            result);

    std::cout << result.size() << ' ' << size << '\n';
    for (const auto& element : result) {
        std::cout << element;
    }
}
