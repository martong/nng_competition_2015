#include "Strategy.hpp"
#include "AttackRun.hpp"
#include "Random.hpp"

Point move(const Table& table, Point pos, Point dest) {
    auto candidate_moves = {p10, p01, -p10, -p01};
    auto min_dist = 1000;
    Point best;
    for (auto i : candidate_moves) {
        Point candidate = pos - i;
        auto d = distance(dest, candidate);
        std::cerr << "  " << candidate << "[" << d << "]\n";
        if (isInsideArray(table, candidate) && min_dist > d) {
            std::cerr << "  update\n";
            best = candidate;
            min_dist = d;
        }
    }
    std::cerr << "  --> " << best << "\n";
    return best;
}

ConquerStrategy::ConquerStrategy() {
    static std::array<Point, 2> dests{{Point{0,19}, Point{19,0}}};
    static std::uniform_int_distribution<std::size_t> dist{0, dests.size() - 1};
    chosenBase = dests[dist(rng)];
    chosenDest = chosenBase;
}

Point ConquerStrategy::eval(const Table& table, Point pos) {
    // keep at the factory
    if (pos == Point{19,19}) {
        return pos;
    }
    // Base reached, go for factory
    if (pos == chosenBase) {
        chosenDest = Point{19,19};
    }
    Point stepTo = move(table, pos, chosenDest);
    return attackRunOverride(table, pos, stepTo, false);
}

DefenseStrategy::DefenseStrategy() {
}

Point DefenseStrategy::eval(const Table& table, Point pos) {
    Soldier type = table[pos]->soldier;
    const Point origin{0, 0};
    Point nearest{19, 19};
    for (Point p : arrayRange(table)) {
        if (table[p] && table[p]->enemy && (table[p]->soldier == type ||
                less(table[p]->soldier, type)) &&
                distance(origin, p) < distance(origin, nearest)) {
            nearest = p;
        }
    }
    Point stepTo = move(table, pos, nearest);
    std::cerr << "Defense: " << pos << " --> " << nearest << " [" <<
            stepTo << "]\n";
    return attackRunOverride(table, pos, stepTo, true);
}

