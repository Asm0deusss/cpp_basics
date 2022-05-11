#pragma once

#include <cstddef>

struct Point {

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    bool operator<=(const Point& other) const;
    bool operator<(const Point& other) const;

    size_t x = 0;
    size_t y = 0;
};
