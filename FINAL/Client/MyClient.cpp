#include "stdafx.h"
#include "Client.h"
#include "parser.h"
#include "Array.hpp"
#include "ArrayIO.hpp"
#include "PointRange.hpp"
#include "Table.hpp"
#include "Response.hpp"
#include "AttackRun.hpp"
#include "Strategy.hpp"
#include <algorithm>
#include <random>
#include <unordered_map>
#include <memory>

std::unordered_map<int, std::shared_ptr<BaseStrategy>> soldierStrategies;

class MYCLIENT : public CLIENT
{
public:
	MYCLIENT();
protected:
	virtual std::string HandleServerResponse(std::vector<std::string> &ServerResponse);
	virtual std::string GetPassword() { return std::string("4Shwna"); } // ACsillag
	virtual std::string GetPreferredOpponents() { return std::string("bot"); }
	virtual bool NeedDebugLog() { return true; }
};

MYCLIENT::MYCLIENT()
{
}

std::string MYCLIENT::HandleServerResponse(std::vector<std::string> &ServerResponse)
{
	PARSER parser;
	parser.Parse(ServerResponse);
	Table table(20, 20);

	// Strategy !!!
	for (auto soldier : parser.soldiers) {
		table[Point{soldier.x, soldier.y}] =
				SoldierData{soldier.id, (Soldier)soldier.t, (bool)soldier.side,
                           SoldierStrategy::offense};
		if (!soldierStrategies.count(soldier.id)) {
			soldierStrategies[soldier.id] = std::make_shared<ConquerStrategy>();
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

	Soldier toProduce = (Soldier)(std::min_element(ours, ours+2) - ours);

    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist{0, 3};
	std::stringstream ss;

	//for (Point p : arrayRange(table)) {
		//const auto& soldier = table[p];
		//if (soldier && !soldier->enemy) {
			//Dir dir;
			//do {
				//dir = (Dir)dist(rng);
			//} while ((dir == Dir::left && p.x == 0) ||
					//(dir == Dir::right && p.x == 19) ||
					//(dir == Dir::top && p.y == 0) ||
					//(dir == Dir::down && p.y == 19));
			//ss << soldier->id << " " << dir << "\n";
		//}
	//}

	for (Point p : arrayRange(table)) {
		const auto& soldier = table[p];
		if (soldier && !soldier->enemy) {
			Point stepTo = soldierStrategies.at(soldier->id)->eval(table, p);
			Dir dir = toDir(p, stepTo);
			ss << soldier->id << " " << dir << "\n";
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
