#include "stdafx.h"
#include "Client.h"
#include "parser.h"
#include "Array.hpp"
#include "ArrayIO.hpp"
#include "PointRange.hpp"

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
	static const char* soldierValues[] = {"rps", "RPS"};
	PARSER parser;
	parser.Parse(ServerResponse);
	Array<char> table(20, 20, '.');
	for (auto soldier : parser.soldiers) {
		table[Point{soldier.x, soldier.y}] =
				soldierValues[soldier.side][soldier.t];
	}
	std::cerr << table;
	std::stringstream ss;
	ss<<"prod R\n";
	ss<<".";
	return ss.str();
}


CLIENT *CreateClient()
{
	return new MYCLIENT();
}
