#include "Soldier.hpp"

#include <vector>

enum class Dir {
    left,
    right,
    top,
    down
};

struct Step {
    int id;
    Dir dir;
};

struct Response {
    std::vector<Step> steps;
    Soldier production;
};
