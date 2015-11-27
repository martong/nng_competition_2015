#include "stdafx.h"
#include "Client.h"
#include "parser.h"
#include "Array.hpp"
#include "ArrayIO.hpp"
#include "PointRange.hpp"
#include "Table.hpp"
#include "Response.hpp"
#include "AttackRun.hpp"
#include "Random.hpp"
#include "Strategy.hpp"
#include <algorithm>
#include <random>
#include  <boost/range/iterator_range_core.hpp>
#include <unordered_map>
#include <memory>

std::unordered_map<int, std::shared_ptr<BaseStrategy>> soldierStrategies;

class MYCLIENT : public CLIENT
{
public:
    MYCLIENT() : prodStrategy(nullptr) {
        std::vector<Soldier> soldiers{Soldier::R, Soldier::P, Soldier::S};
        auto randomSoldiers = randomizedRange(soldiers);
       std::initializer_list<IProdRule*> rules = {
            //new NearestEnemyProdRule(10), new GreaterThanMostProdRule<false>(1),
            //new BalancingProdRule<true>()
           new BalancingProdRule<false>(1), new GreaterThanMostProdRule<false>(1),
           new RandomProdRule()
        };
        prodStrategy = new RuleBasedProdStrategy(rules, randomSoldiers[0]);
     }

protected:
    virtual std::string HandleServerResponse(std::vector<std::string> &ServerResponse);
    virtual std::string GetPassword() { return std::string("4Shwna"); } // ACsillag
    virtual std::string GetPreferredOpponents() { return std::string("any"); }
    virtual bool NeedDebugLog() { return true; }

private:
    IProdStrategy* prodStrategy;
};

std::string MYCLIENT::HandleServerResponse(std::vector<std::string> &ServerResponse)
{
    PARSER parser;
    parser.Parse(ServerResponse);
    Table table(20, 20);

    auto randomizedSoldiers = randomizedRange(parser.soldiers);
    for (auto soldier : randomizedSoldiers) {
        table[Point{soldier.x, soldier.y}] =
                SoldierData{soldier.id, (Soldier)soldier.t, (bool)soldier.side};
        // no strategy yet
        if (!soldierStrategies.count(soldier.id)) {
            soldierStrategies[soldier.id] =
                std::make_shared<ConquerStrategy>(true);
        }
    }
    std::cerr << table;

    std::vector<std::size_t> notOwnedBases;
    for (std::size_t i = 0; i < 2; ++i) {
        if (parser.base_owner[i] != 0) {
            notOwnedBases.push_back(i);
        }
    }

    long ours[] = {
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::R, false}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::P, false}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::S, false}),
    };
    long theirs[] = {
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::R, true}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::P, true}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::S, true}),
    };
    std::cerr << "r=" << ours[0] << "p=" << ours[1] << "s=" << ours[2] << '\n' <<
            "R=" << theirs[0] << "P=" << theirs[1] << "S=" << theirs[2] << '\n';

    //Soldier toProduce = (Soldier)(std::min_element(ours, ours+2) - ours);
    ProdData prodData {table, parser.prod_limit};
    Soldier toProduce = prodStrategy->eval(prodData, parser.prod);

    std::uniform_int_distribution<int> dist{0, 3};
    std::stringstream ss;

    std::map<Soldier, std::vector<int>> soldiersByDistance;
    for (int i = 0; i < 3; ++i) {
        auto localSoldier = Soldier(i);
        std::vector<std::pair<int, Point>> localData;
        for (Point p : arrayRange(table)) {
            const auto& elem = table[p];
            if (elem && !elem->enemy) {
                localData.push_back({elem->id, p});
            }
        }
        std::sort(localData.begin(), localData.end(),
                [](const std::pair<int, Point>& a,
                        const std::pair<int, Point>& b) {
                    return distance(Point{0,0}, a.second)
                            < distance(Point{0,0}, b.second);
                });
        std::vector<int> finalLocalData;
        for (const auto& pair : localData) {
            finalLocalData.push_back(pair.first);
        }
        soldiersByDistance[localSoldier] = finalLocalData;
    }

    std::map<Soldier, std::shared_ptr<BaseStrategy>> strategiesForTypes;
    const int A = 1;
    for (int i = 0; i < 3; ++i) {
        auto soldierType = Soldier(i);

        auto get_n = [&table, &soldierType]() {
            int count = 0;
            for (Point p : arrayRange(table)) {
                const auto& soldier = table[p];
                if (soldier && soldier->enemy &&
                    le(soldierType, soldier->soldier)) {
                    ++count;
                }
            }
            return count;
        };
        auto n = get_n();

        auto get_k = [&table, &soldierType]() {
            int count = 0;
            for (Point p : arrayRange(table)) {
                const auto& soldier = table[p];
                if (soldier && !soldier->enemy &&
                    soldier->soldier == soldierType) {
                    ++count;
                }
            }
            return count;
        };

        auto k = get_k();

        if (n + A > k) {
            strategiesForTypes[soldierType] =
                std::make_shared<DefenseStrategy>();
        } else {
            strategiesForTypes[soldierType] =
                std::make_shared<ConquerStrategy>(true);
        }
    }

    for (Point p : arrayRange(table)) {
        const auto& soldier = table[p];
        if (soldier && !soldier->enemy) {
            const auto& strat = soldierStrategies.at(soldier->id);
            const auto& soldierType = strategiesForTypes.at(soldier->soldier);
            if (soldierType->s == Strategy::Conquer) {
                // Go to the factory
                soldierStrategies[soldier->id] =
                    std::make_shared<ConquerStrategy>(p == Point{0, 0});
                for (const std::size_t i : randomizedRange(notOwnedBases)) {
                    const auto& b = bases[i];
                    const auto& atBase = table[b];
                    // Go to the base
                    if (!atBase || (atBase->enemy &&
                                    less(atBase->soldier, soldier->soldier))) {

                        soldierStrategies[soldier->id] =
                            std::make_shared<BaseConquerStrategy>(i);
                    }
                }
            } else {
                soldierStrategies[soldier->id] =
                    std::make_shared<DefenseStrategy>();
            }

            Point stepTo = strat->eval(table, p);
            std::cerr << p << " --> " << stepTo << "[" << strat->s << "]\n";
            if (stepTo != p) {
                Dir dir = toDir(p, stepTo);
                ss << soldier->id << " " << dir << "\n";
                // refresh the table
                table[p] = boost::none;
                table[stepTo] = soldier;
            }
        }
    }

    //for (Point p : arrayRange(table)) {
        //const auto& soldier = table[p];
        //if (soldier && !soldier->enemy) {
            //// dynamically change the strategy
            //const auto& strat = soldierStrategies.at(soldier->id);
            //if (strat->s == Strategy::Conquer && changeToDefense(table, *soldier)) {
                //std::cerr << soldier->id << " conquer -> defense\n";
                //soldierStrategies[soldier->id] =
                    //std::make_shared<DefenseStrategy>();
            //} else if (strat->s == Strategy::Defense &&
                       //changeToConquer(table, *soldier)) {
                //if (notOwnedBases.empty()) {
                    //std::cerr << soldier->id << " defense -> conquer\n";
                    //soldierStrategies[soldier->id] =
                        //std::make_shared<ConquerStrategy>();
                //} else {
                    //std::cerr << soldier->id << " defense -> base conquer\n";
                    //soldierStrategies[soldier->id] =
                        //std::make_shared<BaseConquerStrategy>(
                                //randomizedRange(notOwnedBases)[0]);
                //}
            //}

            //Point stepTo = strat->eval(table, p);
            //std::cerr << p << " --> " << stepTo << "\n";
            //if (stepTo != p) {
                //Dir dir = toDir(p, stepTo);
                //ss << soldier->id << " " << dir << "\n";
                //// refresh the table
                //table[p] = boost::none;
                //table[stepTo] = soldier;
            //}

        //}
    //}

    ss<<"prod " << toProduce << "\n";
    ss<<".";
    return ss.str();
}


CLIENT *CreateClient()
{
    return new MYCLIENT();
}
