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
    MYCLIENT() : prodStrategy(nullptr) { // TODO
        std::vector<Soldier> soldiers{Soldier::R, Soldier::P, Soldier::S};
        auto randomSoldiers = randomizedRange(soldiers);
        prodStrategy = new NearestEnemyProdStrategy(randomSoldiers[0]);
    }

protected:
    virtual std::string HandleServerResponse(std::vector<std::string> &ServerResponse);
    virtual std::string GetPassword() { return std::string("4Shwna"); } // ACsillag
    virtual std::string GetPreferredOpponents() { return std::string("any"); }
    virtual bool NeedDebugLog() { return true; }

private:
    IProdStrategy* prodStrategy;
    int currentSoldier = 0;
};

std::string MYCLIENT::HandleServerResponse(std::vector<std::string> &ServerResponse)
{
    PARSER parser;
    parser.Parse(ServerResponse);
    Table table(20, 20);

    // Strategy !!!
    auto randomizedSoldiers = randomizedRange(parser.soldiers);
    for (auto soldier : randomizedSoldiers) {
        table[Point{soldier.x, soldier.y}] =
                SoldierData{soldier.id, (Soldier)soldier.t, (bool)soldier.side,
                           SoldierStrategy::offense};
        if (!soldierStrategies.count(soldier.id)) {
             if ((currentSoldier++ % 3 == 2)) {
                soldierStrategies[soldier.id] = std::make_shared<ConquerStrategy>();
             } else {
                soldierStrategies[soldier.id] = std::make_shared<DefenseStrategy>();
             }
        }
    }
    std::cerr << table;

    long ours[] = {
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::R, false, SoldierStrategy::offense}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::P, false, SoldierStrategy::offense}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::S, false, SoldierStrategy::offense}),
    };
    long theirs[] = {
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::R, true, SoldierStrategy::offense}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::P, true, SoldierStrategy::offense}),
        std::count(table.begin(), table.end(),
                SoldierData{0, Soldier::S, true, SoldierStrategy::offense}),
    };
    std::cerr << "r=" << ours[0] << "p=" << ours[1] << "s=" << ours[2] << '\n' <<
            "R=" << theirs[0] << "P=" << theirs[1] << "S=" << theirs[2] << '\n';

    //Soldier toProduce = (Soldier)(std::min_element(ours, ours+2) - ours);
    Soldier toProduce = prodStrategy->eval(table, parser.prod);

    std::uniform_int_distribution<int> dist{0, 3};
    std::stringstream ss;

    for (Point p : arrayRange(table)) {
        const auto& soldier = table[p];
        if (soldier && !soldier->enemy) {
            Point stepTo = soldierStrategies.at(soldier->id)->eval(table, p);
        std::cerr << p << " --> " << stepTo << "\n";
            if (stepTo != p) {
                Dir dir = toDir(p, stepTo);
                ss << soldier->id << " " << dir << "\n";
                // refresh the table
                table[p] = boost::none;
                table[stepTo] = soldier;
            }
        }
    }

    ss<<"prod " << toProduce << "\n";
    ss<<".";
    return ss.str();
}


CLIENT *CreateClient()
{
    return new MYCLIENT();
}
