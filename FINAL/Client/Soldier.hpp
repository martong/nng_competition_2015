#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include <ostream>

enum class Soldier { R, P, S };

inline std::ostream& operator<<(std::ostream& out, const Soldier& soldier) {
    static std::string soldierStrings{"RPS"};
    return out << soldierStrings[static_cast<int>(soldier)];
}

inline bool less(const Soldier& lhs, const Soldier& rhs) {
    return ((lhs == Soldier::P && rhs == Soldier::S) or
            (lhs == Soldier::S && rhs == Soldier::R) or
            (lhs == Soldier::R && rhs == Soldier::P));
}

enum class SoldierStrategy {
    offense, defense, conquer
};


struct SoldierData {
    int id;
    Soldier soldier;
    bool enemy;
    SoldierStrategy strategy;
};

inline bool operator==(const SoldierData& lhs, const SoldierData& rhs) {
    return lhs.soldier == rhs.soldier && lhs.enemy == rhs.enemy;
}

#endif // SOLDIER_HPP
