#pragma once
#include "filter.h"
#include <cmath>

class GaussBlur : public Filter {
public:
    void MakeFilter(Image& image) final;
    explicit GaussBlur(double sigma) : sigma_(sigma){};
    void MakeFrame(const std::vector<std::vector<RGB>>& old_im, std::vector<std::vector<RGB>>& new_im) const;
    ~GaussBlur() override = default;

private:
    double sigma_;
};
