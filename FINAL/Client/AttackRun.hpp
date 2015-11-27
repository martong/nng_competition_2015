#ifndef CLIENT_ATTACKRUN_HPP
#define CLIENT_ATTACKRUN_HPP

#include "Table.hpp"
#include "PointRange.hpp"
#include "Random.hpp"
#include <cstdlib>
#include <set>
#include <assert.h>

inline
Point attackRunOverride(const Table& table, Point p, Point d,
        bool suicidal) {
    assert(std::abs(p.x - d.x) + std::abs(p.y - d.y) == 1);
    assert(table[p]);
    assert(!table[p]->enemy);
    //std::cerr << p << " --> " << d << "\n;
    Soldier mySoldier = table[p]->soldier;
    auto destinations = {p - p10, p + p10, p - p01, p + p01};
    std::set<Point> doNotGo;
    for (Point pp : arrayRange(table)) {
        if (table[pp] && table[pp]->enemy && (
                less(mySoldier, table[pp]->soldier) ||
                        (!suicidal && mySoldier == table[pp]->soldier))) {
            doNotGo.insert(pp + p10);
            doNotGo.insert(pp + p01);
            doNotGo.insert(pp - p10);
            doNotGo.insert(pp - p01);
        }
    }
    for (auto destination : randomizedRange(destinations)) {
        if (!isInsideArray(table, destination)) {
            continue;
        }
        if (table[destination]) {
            if (table[destination]->enemy && (
                    less(table[destination]->soldier, mySoldier) ||
                    (suicidal && table[destination]->soldier == mySoldier))) {
                //std::cerr << "kill " << destination << "\n";
                return destination;
            }
            doNotGo.insert(destination);
        }
    }
    if (doNotGo.count(d) == 0) {
        //std::cerr << "OK " << d << "\n";
        return d;
    }

    for (auto destination : randomizedRange(destinations)) {
        if (isInsideArray(table, destination) && 
                doNotGo.count(destination) == 0) {
            return destination;
        }
    }

    // worst case
    return d;
}


#endif // CLIENT_ATTACKRUN_HPP
