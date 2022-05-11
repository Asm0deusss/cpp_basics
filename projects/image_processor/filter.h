#pragma once
#include "image.h"

class Filter {
public:
    virtual void MakeFilter(Image& image) = 0;
    virtual ~Filter() = default;
};
