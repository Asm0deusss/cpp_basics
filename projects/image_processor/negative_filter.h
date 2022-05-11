#pragma once
#include "filter.h"

class Negative : public Filter {
public:
    void MakeFilter(Image& image) final;
    ~Negative() override = default;
};
