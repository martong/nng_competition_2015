#include "Array.hpp"
#include "Soldier.hpp"
#include <boost/optional.hpp>
#include <ostream>

struct SoldierData {
    Soldier soldier;
    bool enemy;
};

bool operator==(const SoldierData& lhs, const SoldierData& rhs) {
    return lhs.soldier == rhs.soldier && lhs.enemy == rhs.enemy;
}

using TableElement = boost::optional<SoldierData>;
using Table = Array<TableElement>;

inline std::ostream& operator<<(std::ostream& os, TableElement element)  {
    if (!element) {
        return os << '.';
    }
    char c;
    switch (element->soldier) {
        case Soldier::R:
            c = 'r';
            break;
        case Soldier::P:
            c = 'p';
            break;
        case Soldier::S:
            c = 's';
            break;
    }
    if (element->enemy) {
        c -= 32;
    }
    return os << c;
}
