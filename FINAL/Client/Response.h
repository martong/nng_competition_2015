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
    R, S, P
};

struct Prod {
};

struct Response {
    std::vector<Step> steps;
};
