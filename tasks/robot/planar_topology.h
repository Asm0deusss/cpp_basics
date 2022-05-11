#pragma once

#include "topology.h"

class PlanarTopology : public Topology {
public:
    PlanarTopology(const std::vector<std::vector<bool>>& inp) : Topology(inp) {
    }
    std::vector<Point> GetNeighbours(const Point& point) const final;
};
