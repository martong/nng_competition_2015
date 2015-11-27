#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Soldier.hpp"

#include <vector>

enum class Dir {
    left,
    right,
    top,
    down
};

std::ostream& operator<<(std::ostream& out, const Dir& direction){
    static std::vector<std::string> directionStrings{"left", "right", "top",
                "down"};
    return out << directionStrings[static_cast<int>(direction)];
}

struct Step {
    int id;
    Dir dir;
};

struct Response {
    std::vector<Step> steps;
    Soldier production;
};

#endif // RESPONSE_HPP
