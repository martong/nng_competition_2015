#ifndef TOSTRING_HPP
#define TOSTRING_HPP

#include "Response.hpp"

#include <string>
#include <sstream>

static_assert(static_cast<int>(Soldier::R) == 0
        && static_cast<int>(Soldier::P) == 1
        && static_cast<int>(Soldier::S) == 2, "Soldier enum order is changed!");

std::string toString(const Response& response) {
    std::stringstream stream;
    for (const Step& step : response.steps) {
        stream << step.id << step.dir << '\n';
    }
    stream << response.production << '\n';
    return stream.str();
}

#endif // TOSTRING_HPP
