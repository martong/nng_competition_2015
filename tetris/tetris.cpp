#include "Array.hpp"
#include "Point.hpp"
#include "PointRange.hpp"
#include "Hash.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>
#include <vector>
#include <unordered_set>

using Table = Array<bool>;

struct MinMax {
    Point min;
    Point max;
};

MinMax floodFill(Table& table, Point p0) {
    std::vector<Point> pointsToVisit;
    pointsToVisit.reserve(table.width() * table.height());
    pointsToVisit.push_back(p0);

    MinMax result{Point{static_cast<int>(table.width() - 1),
            static_cast<int>(table.height() - 1)}, Point{0, 0}};
    while (!pointsToVisit.empty()) {
        Point p = pointsToVisit.back();
        pointsToVisit.pop_back();

        if (!arrayAt(table, p, true)) {
            result.min.x = std::min(result.min.x, p.x);
            result.min.y = std::min(result.min.y, p.y);
            result.max.x = std::max(result.max.x, p.x);
            result.max.y = std::max(result.max.y, p.y);
            table[p] = true;
            pointsToVisit.push_back(p + p10);
            pointsToVisit.push_back(p - p10);
            pointsToVisit.push_back(p + p01);
            pointsToVisit.push_back(p - p01);
        }
    }

    return result;
}

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

enum class Direction {
    normal, left, right, up
};

struct CompareData {
    Point start;
    Point stepX;
    Point stepY;
};

const CompareData compareDatas[] = {
    {Point{0, 0}, Point{1, 0}, Point{0, 1}}, // normal
    {Point{0, 1}, Point{0, -1}, Point{1, 0}}, // left
    {Point{1, 0}, Point{0, 1}, Point{-1, 0}}, // right
    {Point{1, 1}, Point{-1, 0}, Point{0, -1}}, // up
};

bool compare(const Table& lhs, const Table& rhs, Direction direction) {
    const CompareData& compareData = compareDatas[static_cast<int>(direction)];
    Point startingPoint{
            static_cast<int>(compareData.start.x * (rhs.width() - 1)),
            static_cast<int>(compareData.start.y * (rhs.height() - 1))};

    for (Point p : arrayRange(lhs)) {
        if (lhs[p] != rhs[startingPoint + compareData.stepX * p.x +
                compareData.stepY * p.y]) {
            return false;
        }
    }

    return true;
}

bool operator==(const Table& lhs, const Table& rhs) {
    if (lhs.width() == lhs.height()) {
        if (lhs.width() == rhs.width() && lhs.height() == rhs.height() && (
                compare(lhs, rhs, Direction::normal) ||
                compare(lhs, rhs, Direction::left) ||
                compare(lhs, rhs, Direction::right) ||
                compare(lhs, rhs, Direction::up))) {
            return true;
        }
    } else if (lhs.width() == rhs.width() && lhs.height() == rhs.height()) {
        if (compare(lhs, rhs, Direction::normal) ||
                compare(lhs, rhs, Direction::up)) {
            return true;
        }
    } else if (lhs.height() == rhs.width() && lhs.width() == rhs.height()) {
        if (compare(lhs, rhs, Direction::left) ||
                compare(lhs, rhs, Direction::right)) {
            return true;
        }
    }

    return false;
}

namespace std {

template<>
struct hash<Table> {
    std::size_t operator()(const Table& table) const {
        size_t seed = 0;
        hash_combine(seed, table.width() * table.height());
        hash_combine(seed, std::count(table.begin(), table.end(), true));
        return seed;
    }
};

}

using Tables = std::unordered_set<Table>;

bool hasHole(Table table) {
    for (Point p : arrayRange(table)) {
        if (!table[p]) {
            MinMax minMax = floodFill(table, p);
            if (minMax.min.x != 0 && minMax.min.y != 0 &&
                static_cast<std::size_t>(minMax.max.x) != table.width() - 1 &&
                static_cast<std::size_t>(minMax.max.y) != table.height() - 1) {
                //std::cerr << "-----" << minMax.min << " " << minMax.max << "\n" << table << "-----\n";
                return true;
            }
        }
    }

    return false;
}

static boost::posix_time::ptime start =
        boost::posix_time::microsec_clock::universal_time();

void finish(const Table& table, Tables& result) {
    static std::size_t n = 0;
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

    if (hasHole(croppedTable)) {
        //std::cerr << croppedTable << "\n";
        return;
    }

    if (!result.insert(std::move(croppedTable)).second) {
        return;
    }

    if (++n % 1000 == 0) {
        boost::posix_time::ptime now =
                boost::posix_time::microsec_clock::universal_time();
        std::cerr << n << '(' << now - start << ")\n";
    }
}

void iterate(Table table, std::size_t n, Point p, Tables& result);

void nextIteration(const Table& table, std::size_t n, Point p, Tables& result) {
    if (!table[p]) {
        iterate(table, n, p, result);
    }
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
    }
}
