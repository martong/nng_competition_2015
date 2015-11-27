#ifndef TOSTRING_HPP
#define TOSTRING_HPP

#include "Soldier.hpp"

#include <string>
#include <sstream>

static_assert(static_cast<int>(Soldier::R) == 0
        && static_cast<int>(Soldier::P) == 1
        && static_cast<int>(Soldier::S) == 2, "Soldier enum order is changed!");

std::string toString(const Response& response) {
    static std::vector<std::string> directionString{"left", "right", "top",
                "down"};
    static std::string soldierStrings{"RPS"};
    std::stringstream stream;
    for (const Step& step : response.steps) {
        stream << step.id << directionString[static_cast<int>(step.dir)]
               << '\n';
    }
    stream << soldierStrings[static_cast<int>(response.production)] << '\n';
    return stream.str();
}

#endif // TOSTRING_HPP
