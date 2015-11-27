#include "stdafx.h"
#include "Client.h"
#include "parser.h"
#include "Array.hpp"
#include "ArrayIO.hpp"
#include "PointRange.hpp"
#include "Table.hpp"
#include <algorithm>

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

std::string MYCLIENT::HandleServerResponse(std::vector<std::string> &ServerResponse)
{
	PARSER parser;
	parser.Parse(ServerResponse);
	Table table(20, 20);
	for (auto soldier : parser.soldiers) {
		table[Point{soldier.x, soldier.y}] =
				SoldierData{(Soldier)soldier.t, (bool)soldier.side};
	}
	std::cerr << table;

	long ours[] = {
		std::count(table.begin(), table.end(),
				SoldierData{Soldier::R, false}),
		std::count(table.begin(), table.end(),
				SoldierData{Soldier::P, false}),
		std::count(table.begin(), table.end(),
				SoldierData{Soldier::S, false}),
	};
	long theirs[] = {
		std::count(table.begin(), table.end(),
				SoldierData{Soldier::R, true}),
		std::count(table.begin(), table.end(),
				SoldierData{Soldier::P, true}),
		std::count(table.begin(), table.end(),
				SoldierData{Soldier::S, true}),
	};
	std::cerr << "r=" << ours[0] << "p=" << ours[1] << "s=" << ours[2] << '\n' <<
			"R=" << theirs[0] << "P=" << theirs[1] << "S=" << theirs[2] << '\n';

	Soldier toProduce = (Soldier)(std::min_element(ours, ours+2) - ours);

	std::stringstream ss;
	ss<<"prod " << toProduce << "\n";
	ss<<".";
	return ss.str();
}


CLIENT *CreateClient()
{
	return new MYCLIENT();
}
