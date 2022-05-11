#pragma once
#include "filter.h"
class SobelFilter : public Filter {
public:
    void MakeFilter(Image& im) final;
    ~SobelFilter() override = default;
};
