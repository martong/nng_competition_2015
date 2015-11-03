#ifndef TETRIS_FLOODFILL_HPP
#define TETRIS_FLOODFILL_HPP

#include "Table.hpp"

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

#endif // TETRIS_FLOODFILL_HPP
