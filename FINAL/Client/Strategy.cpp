#include "Strategy.hpp"
#include "AttackRun.hpp"
#include "Random.hpp"

std::array<Point, 2> bases{{Point{19, 0}, Point{0, 19}}};

Point move(const Table& table, Point pos, Point dest) {
    auto candidate_moves = {p10, p01, -p10, -p01};
    auto min_dist = 1000;
    Point best;
    for (auto i : randomizedRange(candidate_moves)) {
        Point candidate = pos - i;
        auto d = distance(dest, candidate);
        //std::cerr << "  " << candidate << "[" << d << "]\n";
        if (isInsideArray(table, candidate) && min_dist > d) {
            //std::cerr << "  update\n";
            best = candidate;
            min_dist = d;
        }
    }
    //std::cerr << "  --> " << best << "\n";
    return best;
}

ConquerStrategy::ConquerStrategy(bool goToBaseFirst)
        : BaseStrategy(Strategy::Conquer) {
    static std::uniform_int_distribution<std::size_t> dist{0, bases.size() - 1};
    chosenBase = bases[dist(rng)];
    if (goToBaseFirst) {
        chosenDest = chosenBase;
    } else {
        chosenDest = Point{19, 19};
    }
}

Point ConquerStrategy::eval(const Table& table, Point pos) {
    // keep at the factory
    if (pos == Point{19,19}) {
        return pos;
    }
    // Base reached, go for factory
    if (pos == chosenBase || (table[chosenBase] && !table[chosenBase]->enemy &&
                distance(pos, chosenBase) < 2)) {
        chosenDest = Point{19,19};
    }
    Point stepTo = move(table, pos, chosenDest);
    return attackRunOverride(table, pos, stepTo, false);
}

BaseConquerStrategy::BaseConquerStrategy(std::size_t base)
        : BaseStrategy(Strategy::BaseConquer) {
    chosenBase = bases[base];
}

Point BaseConquerStrategy::eval(const Table& table, Point pos) {
    // Base reached, go for factory
    if (pos == chosenBase) {
        return chosenBase;
    }
    Point stepTo = move(table, pos, chosenBase);
    return attackRunOverride(table, pos, stepTo, false);
}

Point DefenseStrategy::eval(const Table& table, Point pos) {
    Soldier type = table[pos]->soldier;
    const Point origin{0, 0};
    std::vector<Point> enemies;
    for (Point p : arrayRange(table)) {
        if (table[p] && table[p]->enemy && (table[p]->soldier == type ||
                less(table[p]->soldier, type))) {
            enemies.push_back(p);
        }
    }
    Point nearest;
    if (enemies.empty()) {
        nearest = Point{19, 19};
    } else {
        nearest = *findBest(enemies, 
                [&](Point p) {
                    if (p.x < pos.x && p.y < pos.y) {
                            return distance(p, origin);
                        } else {
                            return distance(p, pos) + 1000;
                        }
                });
    }
    Point stepTo = move(table, pos, nearest);
    //std::cerr << "Defense: " << pos << " --> " << nearest << " [" <<
            //stepTo << "]\n";
    return attackRunOverride(table, pos, stepTo, true);
}

bool changeToDefense(const Table& table, const SoldierData& friendly) {
    for (Point p : arrayRange(table)) {
        const auto& soldier = table[p];
        if (soldier && soldier->enemy) {
            if (le(soldier->soldier, friendly.soldier)) {
                return true;
            }
        }
    }
    return false;
}

bool changeToConquer(const Table& table, const SoldierData& friendly) {
    auto range = arrayRange(table);
    return std::all_of(
        range.begin(), range.end(), [&table, &friendly](Point p) {
            const auto& soldier = table[p];
            if (soldier && soldier->enemy) {
                return greater(soldier->soldier, friendly.soldier);
            } else {
                return true;
            }
        });
}

