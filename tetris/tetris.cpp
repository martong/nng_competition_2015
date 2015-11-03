#include "Array.hpp"
#include "Point.hpp"
#include "PointRange.hpp"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <vector>

using Table = Array<bool>;
using Tables = std::vector<Table>;

void iterate(Table table, std::size_t n, Point p, Tables& result);

void nextIteration(const Table& table, std::size_t n, Point p, Tables& result) {
    if (!table[p]) {
        iterate(table, n, p, result);
    }
}

void finish(const Table& table, Tables& result) {
    Point min{static_cast<int>(table.width()), static_cast<int>(table.height())};
    Point max{0, 0};
    for (Point p : arrayRange(table)) {
        if (table[p]) {
            min.x = std::min(min.x, p.x);
            min.y = std::min(min.y, p.y);
            max.x = std::max(max.x, p.x + 1);
            max.y = std::max(max.y, p.y + 1);
        }
    }

    Table croppedTable{static_cast<std::size_t>(max.x - min.x),
            static_cast<std::size_t>(max.y - min.y)};

    for (Point p : PointRange{min, max}) {
        croppedTable[p - min] = table[p];
    }

    result.push_back(croppedTable);
}

void findNextIteration(const Table& table, std::size_t n, Tables& result) {
    if (n == 0) {
        finish(table, result);
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
        assert(element.width() <= static_cast<std::size_t>(middle));
        assert(element.height() <= static_cast<std::size_t>(middle));
        Point p;
        for (p.y = 0; p.y < middle; ++p.y) {
            for (p.x = 0; p.x < middle; ++p.x) {
                std::cout << (arrayAt(element, p, false) ? 'X' : ' ');
            }
            std::cout << '\n';
        }
        std::cout << "----\n";
    }
}
