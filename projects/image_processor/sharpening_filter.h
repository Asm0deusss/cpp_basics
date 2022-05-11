#pragma once
#include "matrix_filter.h"

class SharpFilter : public MatrixFilter {
public:
    explicit SharpFilter() : MatrixFilter({{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}){};
    ~SharpFilter() override = default;
};
