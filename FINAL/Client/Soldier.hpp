#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include <ostream>

enum class Soldier { R, P, S };

std::ostream& operator<<(std::ostream& out, const Soldier& soldier) {
    static std::string soldierStrings{"RPS"};
    return out << soldierStrings[static_cast<int>(soldier)];
}

bool less(const Soldier& lhs, const Soldier& rhs) {
    return ((lhs == Soldier::P && rhs == Soldier::S) or
            (lhs == Soldier::S && rhs == Soldier::R) or
            (lhs == Soldier::R && rhs == Soldier::P));
}

#endif // SOLDIER_HPP
