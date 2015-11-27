#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "Array.hpp"
#include "parser.h"
#include "Response.hpp"
#include "Point.hpp"
#include "Table.hpp"

#include <boost/optional.hpp>

#include <vector>
#include <numeric>

enum class Strategy {
    Conquer, Defense
};

struct BaseStrategy {
    Strategy s;
    BaseStrategy(Strategy s) : s(s) {}
    virtual Point eval(const Table& table, Point pos) = 0;
};

class ConquerStrategy : public BaseStrategy {
    Point chosenBase;
    Point chosenDest;
public:
    ConquerStrategy(Strategy s);
    virtual Point eval(const Table& table, Point pos) override;
};

class DefenseStrategy : public BaseStrategy {
public:
    DefenseStrategy();
    DefenseStrategy(Strategy s) : BaseStrategy(s) { assert(s == Strategy::Defense); }
    virtual Point eval(const Table& table, Point pos) override;
};

class IProdStrategy {
public:
    virtual Soldier eval(const Table& table, int* ongoing) = 0;
};

class NearestEnemyProdStrategy : public IProdStrategy {
public:
    explicit NearestEnemyProdStrategy(Soldier defaultProd)
            : defaultProd(defaultProd),
              ongoingProd(defaultProd) {
    }

    virtual inline Soldier eval(const Table& table, int* ongoing) override {
        if (std::accumulate(ongoing, ongoing + 3, 0) == 0) {
            ongoingProd = getNextProd(table);
        }
        return ongoingProd;
    }

    Soldier getNextProd(const Table& table) {
        TableElement none = boost::none;
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < i; ++j) {
                Point p{j, i - j};
                const TableElement& elem = arrayAt(table, p, none);
                if (elem && elem->enemy) {
                    return getGreaterSoldier(elem->soldier);
                }
            }
        }
        return defaultProd;
    }

private:
    Soldier defaultProd;
    Soldier ongoingProd;
};

// inline boost::optional<Point> calculateOffensieTarget(const Point& soldierPosition,
//         const Table& array) {

//     std::vector<Point> pointsToVisit;
//     pointsToVisit.push_back(p0);

//     Point result{100, 100}; // BIG distance
//     while (!pointsToVisit.empty()) {
//         if (arrayAt)
//     }

//     return boost::none;
// }

bool changeToDefense(const Table& table, const SoldierData& friendly);
bool changeToConquer(const Table& table, const SoldierData& friendly);

#endif // STRATEGY_HPP
