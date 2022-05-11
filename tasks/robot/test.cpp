#include <catch.hpp>

#include "checkers_topology.h"
#include "knight_topology.h"
#include "overflow_topology.h"
#include "planar_topology.h"
#include "robot.h"
#include "topology.h"
#include "world.h"

#include <algorithm>
#include <unordered_set>

namespace {
std::vector<std::vector<bool>> ParseMap(const std::vector<std::string>& text_map) {
    static const char WALL = '*';

    std::vector<std::vector<bool>> bool_map;

    for (const auto& line : text_map) {
        bool_map.emplace_back();
        std::transform(line.begin(), line.end(), std::back_inserter(bool_map.back()),
                       [](char ch) { return ch == WALL; });
    }

    return bool_map;
}

void RequirePathIsValid(const robot::Path& path, const World& world, const Topology& topology) {
    std::unordered_set<Point> unique_points(path.begin(), path.end());
    REQUIRE(unique_points.size() == path.size());

    if (path.empty()) {
        REQUIRE(topology.MeasureDistance(world.GetStart(), world.GetEnd()) == Topology::UNREACHABLE);
        return;
    }

    if (topology.MeasureDistance(world.GetStart(), world.GetEnd()) == Topology::UNREACHABLE) {
        REQUIRE(path.empty());
    }

    REQUIRE(path.front() == world.GetStart());
    REQUIRE(path.back() == world.GetEnd());

    if (world.GetStart() == world.GetEnd()) {
        REQUIRE(path.size() == 1);
    }

    for (size_t i = 1; i < path.size(); ++i) {
        REQUIRE(topology.MeasureDistance(path[i - 1], path[i]) == 1);
    }
}

}  // namespace

TEST_CASE("RobotPlanar") {
    {
        const auto& map = ParseMap({
            ".*.",
            ".*.",
            "...",
        });

        PlanarTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 0, .y = 0});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);
    }
    {
        const auto& map = ParseMap({
            ".*.",
            ".*.",
            "...",
        });

        PlanarTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 2, .y = 0});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);

        robot::Path expected_path = {
            {.x = 0, .y = 0}, {.x = 0, .y = 1}, {.x = 0, .y = 2}, {.x = 1, .y = 2},
            {.x = 2, .y = 2}, {.x = 2, .y = 1}, {.x = 2, .y = 0},
        };
        REQUIRE(path == expected_path);
    }
    {
        const auto& map = ParseMap({
            ".*.",
            ".*.",
            ".*.",
        });

        PlanarTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 2, .y = 2});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);
    }
}

TEST_CASE("RobotOverflow") {
    {
        const auto& map = ParseMap({
            ".*.",
            "***",
            "**.",
        });

        OverflowTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 2, .y = 2});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);

        robot::Path expected_path = {
            {.x = 0, .y = 0},
            {.x = 2, .y = 0},
            {.x = 2, .y = 2},
        };

        REQUIRE(path == expected_path);
    }
    {
        const auto& map = ParseMap({
            ".***",
            ".*.*",
            ".***",
        });

        OverflowTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 2, .y = 1});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);
    }
}

TEST_CASE("RobotCheckers") {
    {
        const auto& map = ParseMap({
            ".*......",
            "*.*.....",
            "..*.*.*.",
            "........",
        });

        CheckersTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 4, .y = 0});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);

        robot::Path expected_path = {
            {.x = 0, .y = 0},
            {.x = 1, .y = 1},
            {.x = 5, .y = 1},
            {.x = 4, .y = 0},
        };

        REQUIRE(path == expected_path);
    }
    {
        const auto& map = ParseMap({
            "..",
            "..",
        });

        CheckersTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 1, .y = 0});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);
    }
}

TEST_CASE("RobotKnight") {
    {
        const auto& map = ParseMap({
            ".*.",
            "***",
            "...",
        });

        KnightTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 2, .y = 0});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);

        robot::Path expected_path = {
            {.x = 0, .y = 0},
            {.x = 1, .y = 2},
            {.x = 2, .y = 0},
        };

        REQUIRE(path == expected_path);
    }
    {
        const auto& map = ParseMap({
            ".*.",
            "*..",
            "...",
        });

        KnightTopology topology(map);
        World world(topology, Point{.x = 0, .y = 0}, Point{.x = 2, .y = 2});
        const auto& path = robot::FindPath(world);

        RequirePathIsValid(path, world, topology);
    }
}

TEST_CASE("IllegalMove") {
    const auto& map = ParseMap({
        ".*.",
        ".*.",
        "...",
    });

    PlanarTopology topology(map);
    World world(topology, Point{.x = 0, .y = 0}, Point{.x = 2, .y = 2});

    try {
        world.Move(world.GetEnd());
    } catch (const World::IllegalMoveException&) {
        return;
    }

    FAIL("Expected World::IllegalMoveException");
}
