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

ConquerStrategy::ConquerStrategy() {
    static std::array<Point, 3> dests{{Point{19,19}, Point{0,19}, Point{19,0}}};
    static std::uniform_int_distribution<std::size_t> dist{0, dests.size() - 1};
    chosenDest = dests[dist(rng)];
}

Point ConquerStrategy::eval(const Table& table, Point pos) {
    Point stepTo = move(table, pos, chosenDest);
    return attackRunOverride(table, pos, stepTo);
}

