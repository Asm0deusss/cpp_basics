#include "robot.h"
robot::Path robot::FindPath(World& world) {

    using Distance = ssize_t;

    robot::Path ans;
    Point min_point = world.GetCurrentPosition();
    std::set<Point> seen;
    ans.push_back(min_point);
    ssize_t min_path = Topology::UNREACHABLE;

    if (!world.IsGood(world.GetEnd())) {
        return {};
    }

    while (world.GetCurrentPosition() != world.GetEnd()) {
        std::unordered_map<Point, Distance> look = world.Lookup();
        for (const auto& i : look) {
            if (seen.contains(i.first)) {
                continue;
            }

            if (min_path == Topology::UNREACHABLE) {
                if (i.second != Topology::UNREACHABLE) {
                    min_path = i.second;
                    min_point = i.first;
                }
            } else if (i.second != Topology::UNREACHABLE && i.second < min_path) {
                min_path = i.second;
                min_point = i.first;
            }

            seen.insert(i.first);
        }

        if (min_point == world.GetCurrentPosition()) {
            return {};
        }

        seen.insert(min_point);
        ans.push_back(min_point);
        world.Move(min_point);
    }

    return ans;
}
