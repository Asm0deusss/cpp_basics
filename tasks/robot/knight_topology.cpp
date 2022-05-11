#include "knight_topology.h"
#include <cmath>
std::vector<Point> KnightTopology::GetNeighbours(const Point& point) const {
    if (field_[point.y][point.x]) {
        return {};
    }

    std::vector<Point> ans;

    ssize_t x = point.x;
    ssize_t y = point.y;

    std::vector<std::pair<ssize_t, ssize_t>> check = {{x - 2, y - 1}, {x - 2, y + 1}, {x - 1, y - 2}, {x - 1, y + 2},
                                                      {x + 2, y - 1}, {x + 2, y + 1}, {x + 1, y - 2}, {x + 1, y + 2}};

    Topology::CheckPoint(ans, check);

    return ans;
}
