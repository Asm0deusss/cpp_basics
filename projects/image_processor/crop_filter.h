#pragma once
#include "filter.h"

class Crop : public Filter {
public:
    Crop(size_t width, size_t height) : width_(width), height_(height){};
    void MakeFilter(Image& image) final;
    ~Crop() override = default;

private:
    size_t width_;
    size_t height_;
};
