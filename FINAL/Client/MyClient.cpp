#include "stdafx.h"
#include "Client.h"
#include "parser.h"
#include "Array.hpp"
#include "ArrayIO.hpp"
#include "PointRange.hpp"
#include "Table.hpp"
#include "Response.hpp"
#include <algorithm>
#include <random>

// sample

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

Point move(const Table&, Point pos, Point dest) {
	auto candidate_moves = {p10, p01, -p10, -p01};
	auto min_dist = 1000;
	Point best;
	for (auto i : candidate_moves) {
		Point candidate = pos - i;
		if (min_dist > distance(dest, candidate)) {
			best = candidate;
		}
	}
	return best;
}

std::string MYCLIENT::HandleServerResponse(std::vector<std::string> &ServerResponse)
{
	PARSER parser;
	parser.Parse(ServerResponse);
	Table table(20, 20);
	for (auto soldier : parser.soldiers) {
		table[Point{soldier.x, soldier.y}] =
				SoldierData{soldier.id, (Soldier)soldier.t, (bool)soldier.side};
	}
	std::cerr << table;

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
			Dir dir;
			Point stepTo = move(table, p, Point(19,19));

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
