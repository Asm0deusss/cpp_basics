#pragma once
#include <iostream>
#include <vector>
#include "rgb.h"
#include "bmp.h"
struct Image {
    // Constructors and destructors
    Image();
    Image(size_t width, size_t height);
    ~Image() = default;

    // Getters and setters
    const RGB& GetColor(const size_t x, const size_t y) const;
    void SetColor(const RGB& color, const size_t x, const size_t y);

    size_t width_;
    size_t height_;
    std::vector<std::vector<RGB> > data_;
};
