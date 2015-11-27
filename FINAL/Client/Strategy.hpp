#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "parser.h"
#include "Response.hpp"
#include "Point.hpp"
#include "Table.hpp"

#include <vector>

class BaseStrategy {
public:
    virtual Point eval(const Table& table, Point pos) = 0;
};

class ConquerStrategy : public BaseStrategy {
public:
    Point chosenBase = Point(19,0);
    virtual Point eval(const Table& table, Point pos) override;
};

#endif // STRATEGY_HPP
