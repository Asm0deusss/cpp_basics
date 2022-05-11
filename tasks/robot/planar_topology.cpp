#include "planar_topology.h"
std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    if (field_[point.y][point.x]) {
        return {};
    }

    std::vector<Point> ans;

    ssize_t x = point.x;
    ssize_t y = point.y;

    std::vector<std::pair<ssize_t, ssize_t>> check = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};

    Topology::CheckPoint(ans, check);

    return ans;
}
