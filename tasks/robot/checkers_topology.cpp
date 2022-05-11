#include "checkers_topology.h"
#include <set>
#include <queue>

#include <iostream>

std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    if (field_[point.y][point.x]) {
        return {};
    }

    std::vector<Point> ans;
    std::set<Point> seen;

    std::queue<Point> q;
    q.push(point);

    while (!q.empty()) {
        size_t x = q.front().x;
        size_t y = q.front().y;

        if (seen.contains(q.front())) {
            q.pop();
            continue;
        }

        if (x >= 2) {
            if (y >= 2 && !field_[y - 2][x - 2] && field_[y - 1][x - 1] &&
                !seen.contains(Point{.x = x - 2, .y = y - 2})) {

                ans.push_back(Point{.x = x - 2, .y = y - 2});
                q.push(Point{.x = x - 2, .y = y - 2});
            }

            if (y + 3 <= height_ && !field_[y + 2][x - 2] && field_[y + 1][x - 1] &&
                !seen.contains(Point{.x = x - 2, .y = y + 2})) {

                ans.push_back(Point{.x = x - 2, .y = y + 2});
                q.push(Point{.x = x - 2, .y = y + 2});
            }
        }

        if (q.front() == point && x >= 1) {
            if (y >= 1 && !field_[y - 1][x - 1] && !seen.contains(Point{.x = x - 1, .y = y - 1})) {

                seen.insert(Point{.x = x - 1, .y = y - 1});
                ans.push_back(Point{.x = x - 1, .y = y - 1});
            }

            if (y + 2 <= height_ && !field_[y + 1][x - 1] && !seen.contains(Point{.x = x - 1, .y = y + 1})) {

                seen.insert(Point{.x = x - 1, .y = y + 1});
                ans.push_back(Point{.x = x - 1, .y = y + 1});
            }
        }

        if (x + 3 <= width_) {
            if (y >= 2 && !field_[y - 2][x + 2] && field_[y - 1][x + 1] &&
                !seen.contains(Point{.x = x + 2, .y = y - 2})) {

                ans.push_back(Point{.x = x + 2, .y = y - 2});
                q.push(Point{.x = x + 2, .y = y - 2});
            }

            if (y + 3 <= height_ && !field_[y + 2][x + 2] && field_[y + 1][x + 1] &&
                !seen.contains(Point{.x = x + 2, .y = y + 2})) {

                ans.push_back(Point{.x = x + 2, .y = y + 2});
                q.push(Point{.x = x + 2, .y = y + 2});
            }
        }

        if (q.front() == point && x + 2 <= width_) {
            if (y >= 1 && !field_[y - 1][x + 1] && !seen.contains(Point{.x = x + 1, .y = y - 1})) {

                seen.insert(Point{.x = x + 1, .y = y - 1});
                ans.push_back(Point{.x = x + 1, .y = y - 1});
            }

            if (y + 2 <= height_ && !field_[y + 1][x + 1] && !seen.contains(Point{.x = x + 1, .y = y + 1})) {

                seen.insert(Point{.x = x + 1, .y = y + 1});
                ans.push_back(Point{.x = x + 1, .y = y + 1});
            }
        }
        seen.insert(q.front());
        q.pop();
    }

    return ans;
}
