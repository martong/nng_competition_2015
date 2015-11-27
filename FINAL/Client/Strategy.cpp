#include "Strategy.hpp"
#include "AttackRun.hpp"

Point move(const Table& table, Point pos, Point dest) {
    auto candidate_moves = {p10, p01, -p10, -p01};
    auto min_dist = 1000;
    Point best;
    for (auto i : candidate_moves) {
        Point candidate = pos - i;
        auto d = distance(dest, candidate);
        std::cerr << candidate << " " << d << std::endl;
        if (isInsideArray(table, candidate) && min_dist > d) {
            best = candidate;
            min_dist = d;
            std::cerr << "frissitve " << pos << " " << best << "\n";
        }
    }
    std::cerr << "\n";
    return best;
}


Point ConquerStrategy::eval(const Table& table, Point pos) {
    //Point stepTo = move(table, pos, Point(19,19));
    Point stepTo = move(table, pos, Point(6,2));
    return attackRunOverride(table, pos, stepTo, false);
}

