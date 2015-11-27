enum class Soldier {
    R,
    P,
    S
};

bool operator<(const Soldier& lhs, const Soldier& rhs) {
    if ((lhs == Soldier::P && rhs == Soldier::S) or
        (lhs == Soldier::S && rhs == Soldier::R) or
        (lhs == Soldier::R && rhs == Soldier::P)) {
        return true;
    }
    return false;
}
