#include "overflow_topology.h"
std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    if (field_[point.y][point.x]) {
        return {};
    }

    std::vector<Point> ans;

    ssize_t x = point.x;
    ssize_t y = point.y;

    if (x == 0) {
        x = width_;
    }
    if (y == 0) {
        y = height_;
    }
    std::vector<std::pair<ssize_t, ssize_t>> check = {
        {(x + 1) % width_, y % height_}, {x - 1, y % height_}, {x % width_, y - 1}, {x % width_, (y + 1) % height_}};

    Topology::CheckPoint(ans, check);

    return ans;
}
