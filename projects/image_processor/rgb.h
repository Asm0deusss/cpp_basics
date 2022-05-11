#pragma once

struct RGB {
public:
    int r;
    int g;
    int b;
    RGB() : r(0), g(0), b(0){};
    RGB(int r, int g, int b) : r(r), g(g), b(b){};
    ~RGB() = default;
};
