#pragma once

#include "point.h"
#include "topology.h"

#include <exception>
#include <unordered_map>
#include <iostream>

namespace std {

template <>
struct hash<Point> {
    std::size_t operator()(const Point& point) const {
        std::size_t h1 = std::hash<size_t>{}(point.x);
        std::size_t h2 = std::hash<size_t>{}(point.y);
        return h1 ^ (h2 << 1);
    }
};

}  // namespace std

class World {
public:
    class IllegalMoveException : public std::exception {};

    World(const Topology& topology, Point start, Point end);

    std::unordered_map<Point, Topology::Distance> Lookup() const;

    const Point& GetStart() const;
    const Point& GetEnd() const;
    const Point& GetCurrentPosition() const;

    bool IsGood(const Point& point) const;

    void Move(const Point& to);

private:
    std::unordered_map<Point, std::vector<Point>> neighbours_;
    std::unordered_map<Point, Topology::Distance> distances_;
    Point start_;
    Point end_;
    Point cur_;
};
