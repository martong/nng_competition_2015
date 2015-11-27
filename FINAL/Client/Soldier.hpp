#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include <ostream>

enum class Soldier { R, P, S };

inline Soldier getGreaterSoldier(Soldier s) {
    int v = static_cast<int>(s), g = 0;
    if (v < 2) {
        g = v + 1;
    }
    return static_cast<Soldier>(g);
}

inline std::ostream& operator<<(std::ostream& out, const Soldier& soldier) {
    static std::string soldierStrings{"RPS"};
    return out << soldierStrings[static_cast<int>(soldier)];
}

inline bool less(const Soldier& lhs, const Soldier& rhs) {
    return ((lhs == Soldier::P && rhs == Soldier::S) or
            (lhs == Soldier::S && rhs == Soldier::R) or
            (lhs == Soldier::R && rhs == Soldier::P));
}

inline bool greater(const Soldier& lhs, const Soldier& rhs) {
    return less(rhs, lhs);
}

inline bool le(const Soldier& lhs, const Soldier& rhs) {
    return less(lhs, rhs) || lhs == rhs;
}

inline bool ge(const Soldier& lhs, const Soldier& rhs) {
    return greater(lhs, rhs) || lhs == rhs;
}


struct SoldierData {
    int id;
    Soldier soldier;
    bool enemy;
};

inline bool operator==(const SoldierData& lhs, const SoldierData& rhs) {
    return lhs.soldier == rhs.soldier && lhs.enemy == rhs.enemy;
}

#endif // SOLDIER_HPP
