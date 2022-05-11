#include "image.h"
Image::Image() {
    width_ = 0;
    height_ = 0;
    data_ = {};
}
Image::Image(size_t width, size_t height) {
    if (width == 0 || height == 0) {
        throw std::runtime_error("Bad size");
    }
    width_ = width;
    height_ = height;
    data_ = std::vector<std::vector<RGB>>(height, std::vector<RGB>(width, RGB()));
}

const RGB& Image::GetColor(const size_t x, const size_t y) const {
    if (!(0 <= x && x < width_ && 0 <= y && y < height_)) {
        throw std::runtime_error("Out of range");
    }
    return data_[y][x];
}

void Image::SetColor(const RGB& color, const size_t x, const size_t y) {
    if (!(0 <= x && x < width_ && 0 <= y && y < height_)) {
        throw std::runtime_error("Out of range");
    }
    data_[y][x] = color;
}
