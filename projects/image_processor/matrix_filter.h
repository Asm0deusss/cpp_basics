#pragma once
#include "filter.h"

class MatrixFilter : virtual public Filter {
public:
    explicit MatrixFilter(std::vector<std::vector<ssize_t>> mat) : matrix_(std::move(mat)){};
    void MakeFilter(Image& im) override;
    ~MatrixFilter() override = default;

protected:
    void MakeNewImage(const std::vector<std::vector<RGB>>& old_im, std::vector<std::vector<RGB>>& new_im);
    std::vector<std::vector<ssize_t>> matrix_;
};
