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
    Point chosenDest;
public:
    ConquerStrategy();
    virtual Point eval(const Table& table, Point pos) override;
};

#endif // STRATEGY_HPP
