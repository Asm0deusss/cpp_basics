#pragma once

#include "topology.h"

class KnightTopology : public Topology {
public:
    KnightTopology(const std::vector<std::vector<bool>>& inp) : Topology(inp) {
    }
    std::vector<Point> GetNeighbours(const Point& point) const final;
};
