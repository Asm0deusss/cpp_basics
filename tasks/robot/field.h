#pragma once
#include <vector>
#include <iostream>

class Field {
public:
    Field(const std::vector<std::vector<bool>>& inp);
    const size_t GetWidth() const;
    const size_t GetHeight() const;

protected:
    size_t height_;
    size_t width_;
    std::vector<std::vector<bool>> field_;
};