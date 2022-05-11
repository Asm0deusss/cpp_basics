#include "topology.h"
const Topology::Distance Topology::UNREACHABLE;

Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {

    std::vector<std::vector<Distance>> distances = std::vector(height_, std::vector(width_, Topology::UNREACHABLE));
    if (field_[from.y][from.x] || field_[to.y][to.x]) {
        return Topology::UNREACHABLE;
    }

    std::set<Point> seen;
    std::queue<Point> q;
    q.push(from);

    distances[from.y][from.x] = 0;

    while (!q.empty()) {
        size_t x = q.front().x;
        size_t y = q.front().y;

        if (seen.contains(q.front())) {
            q.pop();
            continue;
        }

        std::vector<Point> neighbours = GetNeighbours(q.front());
        for (const auto& i : neighbours) {

            if (distances[i.y][i.x] > distances[y][x] + 1 || distances[i.y][i.x] == Topology::UNREACHABLE) {
                distances[i.y][i.x] = distances[y][x] + 1;
            }
            if (!seen.contains(i)) {
                q.push(i);
            }
        }
        seen.insert(q.front());
        q.pop();
    }

    return distances[to.y][to.x];
}
void Topology::CheckPoint(std::vector<Point>& ans, std::vector<std::pair<ssize_t, ssize_t>>& check) const {
    for (const auto& [check_x, check_y] : check) {
        if (check_x >= 0 && check_x < width_ && check_y >= 0 && check_y < height_ && !field_[check_y][check_x]) {
            ans.push_back(Point{.x = static_cast<size_t>(check_x), .y = static_cast<size_t>(check_y)});
        }
    }
}
