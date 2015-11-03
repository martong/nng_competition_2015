#ifndef TETRIS_POINT_HPP
#define TETRIS_POINT_HPP

#include "Hash.hpp"

#include <ostream>
#include <stddef.h>

class Point {
public:
    int x, y;
    Point():x(0), y(0) { }
    explicit constexpr Point(int x, int y):x(x), y(y) {}

    constexpr Point(const Point&) = default;
    Point& operator=(const Point&) = default;

    Point& operator+=(Point other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Point& operator-=(Point other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Point& operator*=(int n)
    {
        x *= n;
        y *= n;
        return *this;
    }
};

constexpr Point p10{1, 0}, p01{0, 1}, p11{1, 1};

inline constexpr bool operator==(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

inline constexpr bool operator!=(Point p1, Point p2) {
    return !(p1 == p2);
}

inline constexpr Point operator+(Point p1, Point p2) {
    return Point(p1.x+p2.x, p1.y+p2.y);
}

inline constexpr Point operator-(Point p1, Point p2) {
    return Point(p1.x-p2.x, p1.y-p2.y);
}

inline constexpr Point operator*(Point p, int n) {
    return Point(p.x*n, p.y*n);
}

inline constexpr Point operator-(Point p) {
    return p * -1;
}

inline constexpr bool operator<(Point p1, Point p2) {
    return p1.y < p2.y || (p1.y == p2.y && p1.x < p2.x);
}

inline
std::ostream& operator<<(std::ostream& os, Point p) {
    return os << '(' << p.x << ", " << p.y << ')';
}

namespace std {

template<>
struct hash<Point> {
    size_t operator()(Point p) const {
        size_t seed = 0;
        hash_combine(seed, p.x);
        hash_combine(seed, p.y);
        return seed;
    }
};

} // namespace std

#endif // TETRIS_POINT_HPP