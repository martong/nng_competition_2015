#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "parser.h"
#include "Response.php"

#include <vector>

class MoveStrategy {
public:
    virtual std::vector<Step> evaluate(const PARSER& input) = 0;
};

class ProductionStrategy {
public:
    virtual Soldier evaluate(const PARSER& input) = 0;
};

#endif // STRATEGY_HPP
