#include "point.h"

bool Point::operator==(const Point& other) const {
    return (x == other.x && y == other.y);
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

bool Point::operator<=(const Point& other) const {
    return (x < other.x || (x == other.x && y <= other.y));
}

bool Point::operator<(const Point& other) const {
    if (x < other.x) {
        return true;
    }
    if (x == other.x && y < other.y) {
        return true;
    }
    return false;
}
