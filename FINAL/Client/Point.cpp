#include "Point.hpp"

#include <cassert>

std::string direction(Point d)
{
    return
            d.x > 0 ? "right" :
            d.x < 0 ? "left" :
            d.y > 0 ? "down" :
            d.y < 0 ? "up" : "???";
}

std::ostream& operator<<(std::ostream& os, Point p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}

Dir toDir(const Point& source, const Point& destination) {
    Point diff = destination - source;
    if (diff == p10) {
        return Dir::right;
    } else if (diff == p01) {
        return Dir::down;
    } else if (diff == p11) {
        assert(false);
    } else if (diff*-1 == p10) {
        return Dir::up;
    } else if (diff*-1 == p01) {
        return Dir::left;
    } else if (diff*-1 == p11) {
        assert(false);
    } else {
        assert(false);
    }
    assert(false);
}
