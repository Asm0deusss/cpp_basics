#pragma once
#include "matrix_filter.h"
#include "grayscale_filter.h"

class EdgeDetection : public MatrixFilter, public GrayScale{
public:
    explicit EdgeDetection(const float par) : MatrixFilter({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}), par_(par) {};
    void MakeFilter(Image& im) final;
    ~EdgeDetection() override = default;
private:
    float par_;
};

