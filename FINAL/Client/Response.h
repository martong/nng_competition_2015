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

enum class Soldier {
    R, P, S
};

struct Response {
    std::vector<Step> steps;
    Soldier production;
};
