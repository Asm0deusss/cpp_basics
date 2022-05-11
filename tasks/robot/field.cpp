#include "field.h"

Field::Field(const std::vector<std::vector<bool>>& inp) : height_(inp.size()), width_(inp[0].size()), field_(inp) {
}
const size_t Field::GetWidth() const {
    return width_;
}

const size_t Field::GetHeight() const {
    return height_;
}
