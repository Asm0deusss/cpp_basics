#include "world.h"

const Point& World::GetStart() const {
    return start_;
}

const Point& World::GetEnd() const {
    return end_;
}

const Point& World::GetCurrentPosition() const {
    return cur_;
}

void World::Move(const Point& to) {
    if (std::count(neighbours_.at(cur_).begin(), neighbours_.at(cur_).end(), to) == 0) {
        throw IllegalMoveException();
    }
    cur_ = to;
}

World::World(const Topology& topology, Point start, Point end) {
    start_ = start;
    end_ = end;

    for (size_t i = 0; i < topology.GetHeight(); ++i) {
        for (size_t j = 0; j < topology.GetWidth(); ++j) {
            neighbours_[Point{.x = j, .y = i}] = topology.GetNeighbours(Point{.x = j, .y = i});
            distances_[Point{.x = j, .y = i}] = topology.MeasureDistance(Point{.x = j, .y = i}, end_);
        }
    }
}

std::unordered_map<Point, Topology::Distance> World::Lookup() const {
    std::unordered_map<Point, Topology::Distance> ans;

    for (const auto& i : neighbours_.at(cur_)) {
        ans[i] = distances_.at(i);
    }

    return ans;
}
bool World::IsGood(const Point& point) const {
    if (distances_.at(point) != Topology::UNREACHABLE) {
        return true;
    }
    return false;
}
