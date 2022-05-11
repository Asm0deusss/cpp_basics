#pragma once

#include "point.h"
#include "field.h"
#include <vector>
#include <queue>
#include <set>

class Topology : public Field {
public:
    using Distance = ssize_t;

    virtual std::vector<Point> GetNeighbours(const Point& point) const = 0;
    Distance MeasureDistance(const Point& from, const Point& to) const;

    Topology(const std::vector<std::vector<bool>>& inp) : Field(inp){};

    static const Distance UNREACHABLE = -1;

protected:
    void CheckPoint(std::vector<Point>& ans, std::vector<std::pair<ssize_t, ssize_t>>& check) const;
};
