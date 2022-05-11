#pragma once

#include "world.h"

namespace robot {

using Path = std::vector<Point>;

Path FindPath(World& world);

}  // namespace robot
