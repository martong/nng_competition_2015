#ifndef CLIENT_ATTACKRUN_HPP
#define CLIENT_ATTACKRUN_HPP

#include "Table.hpp"
#include "PointRange.hpp"
#include <cstdlib>
#include <set>
#include <assert.h>

Point attackRunOverride(const Table& table, Point p, Point d) {
    assert(std::abs(p.x - d.x) + std::abs(p.y - d.y) == 1);
    assert(table[p]);
    assert(!table[p]->enemy);
    Soldier mySoldier = table[p]->soldier;
    auto destinations = {p - p10, p + p10, p - p01, p + p01};
    std::set<Point> doNotGo;
    for (Point pp : arrayRange(table)) {
        if (table[pp] && table[pp]->enemy && less(mySoldier, table[pp]->soldier)) {
            doNotGo.insert(pp + p10);
            doNotGo.insert(pp + p01);
            doNotGo.insert(pp - p10);
            doNotGo.insert(pp - p01);
        }
    }
    for (auto destination : destinations) {
        if (table[destination] && table[destination]->enemy) {
            if (less(table[destination]->soldier, mySoldier)) {
                return destination;
            }
            doNotGo.insert(destination);
        }
    }
    if (doNotGo.count(d) == 0) {
        return d;
    }

    for (auto destination : destinations) {
        if (doNotGo.count(d) == 0) {
            return destination;
        }
    }

    // worst case
    return d;
}


#endif // CLIENT_ATTACKRUN_HPP
