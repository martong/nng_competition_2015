#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "Array.hpp"
#include "parser.h"
#include "Point.hpp"
#include "Response.hpp"
#include "Random.hpp"
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

//============================================================================//

struct ProdData {
    Table table;
    int prodTime;
};

class IProdStrategy {
public:
    virtual Soldier eval(const ProdData& data, int* ongoing) = 0;
};

class NearestEnemyProdStrategy : public IProdStrategy {
public:
    explicit NearestEnemyProdStrategy(Soldier defaultProd)
            : defaultProd(defaultProd),
              ongoingProd(defaultProd) {
    }

    virtual inline Soldier eval(const ProdData& data, int* ongoing) override {
        if (std::accumulate(ongoing, ongoing + 3, 0) == 0) {
            ongoingProd = getNextProd(data.table);
        }
        return ongoingProd;
    }

    inline Soldier getNextProd(const Table& table) {
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

class IProdRule {
public:
    virtual void setData(const ProdData& data) = 0;
    virtual bool isFireable() {
        return true;
    }

    virtual Soldier getSoldier() = 0;
};

class RuleBasedProdStrategy : public IProdStrategy {
public:
    RuleBasedProdStrategy(std::initializer_list<IProdRule*> rules,
            Soldier defaultProd)
            : rules(rules),
              ongoingProd(defaultProd) {
    }

    virtual inline Soldier eval(const ProdData& data, int* ongoing) override {
        if (std::accumulate(ongoing, ongoing + 3, 0) == 0) {
            ongoingProd = getNextProd(data);
        }
        //std::cerr << "Prod: " << ongoingProd << std::endl;
        return ongoingProd;
   }

private:
    Soldier getNextProd(const ProdData& data) {
        for (IProdRule* rule : rules) {
            //std::cerr << "next prod rule..." << std::endl;
            rule->setData(data);
            if (rule->isFireable()) {
                //std::cerr << "prod rule matched" << std::endl;
                return rule->getSoldier();
            }
        }
        assert(false); // should never happen, at least one rule must be fired
    }

    std::vector<IProdRule*> rules;
    Soldier defaultProd;
    Soldier ongoingProd;
};

class NearestEnemyProdRule : public IProdRule {
public:
    explicit NearestEnemyProdRule(int threshold) : threshold(threshold) {
    }

    virtual void setData(const ProdData& data) override {
        nearestSoldier = findNearestSoldier(data.table);
    }

    virtual bool isFireable() override {
        return nearestSoldier &&
                ((nearestPoint->x + nearestPoint->y) < threshold + prodTime);
    }

    virtual Soldier getSoldier() override {
        assert(nearestSoldier);
        return getGreaterSoldier(nearestSoldier->soldier);
    }

private:
    inline boost::optional<SoldierData> findNearestSoldier(const Table& table) {
        TableElement none = boost::none;
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < i; ++j) {
                Point p{j, i - j};
                const TableElement& elem = arrayAt(table, p, none);
                if (elem && elem->enemy) {
                    nearestPoint = p;
                    return elem;
                }
            }
        }
        return boost::none;
    }

    const int threshold;
    TableElement nearestSoldier;
    boost::optional<Point> nearestPoint;
    int prodTime;
};

class GreaterThanMostProdRule : public IProdRule {
public:
    explicit GreaterThanMostProdRule(int threshold) : threshold(threshold) {
    }

    virtual void setData(const ProdData& data) override {
        for (TableElement elem : data.table) {
            if (elem && elem->enemy) {
                ++counters[elem->soldier];
            }
        }
        auto it = std::max_element(counters.begin(), counters.end(),
                [](const std::pair<Soldier, int>& a,
                        const std::pair<Soldier, int>& b) {
                    return a.second < b.second;
                });
        enemySoldier = it->first;
        //std::cerr << "greaterThanMost, found max enemy: " << enemySoldier << std::endl;
    }

    virtual bool isFireable() override {
        int max = std::max({
                    std::abs(counters[Soldier::R] - counters[Soldier::P]),
                    std::abs(counters[Soldier::R] - counters[Soldier::S]),
                    std::abs(counters[Soldier::S] - counters[Soldier::P])});
        return max > threshold;
    }

    virtual Soldier getSoldier() override {
        return getGreaterSoldier(enemySoldier);
    }

private:
    const int threshold;
    std::map<Soldier, int> counters;
    Soldier enemySoldier;
};

class RandomProdRule : public IProdRule {
public:
    virtual void setData(const ProdData& /*data*/) override {
    }

    virtual Soldier getSoldier() override {
        std::vector<Soldier> soldiers{Soldier::R, Soldier::P, Soldier::S};
        auto randomizedSoldiers = randomizedRange(soldiers);
        return randomizedSoldiers[0];
    }
};

class BalancingProdRule : public IProdRule {
public:
    virtual void setData(const ProdData& data) override {
        for (TableElement elem : data.table) {
            if (elem && !elem->enemy) {
                ++counters[elem->soldier];
            }
        }
        auto it = std::min_element(counters.begin(), counters.end(),
                [](const std::pair<Soldier, int>& a,
                        const std::pair<Soldier, int>& b) {
                    return a.second < b.second;
                });
        soldier = it->first;
        //std::cerr << "BalancingPR, found min elem: " << soldier << std::endl;
    }

    virtual Soldier getSoldier() override {
        return soldier;
    }

private:
    std::map<Soldier, int> counters;
    Soldier soldier;
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
