#pragma once
#include "filter.h"

class GrayScale : virtual public Filter {
public:
    void MakeFilter(Image& image) override;
    ~GrayScale() override = default;
};
