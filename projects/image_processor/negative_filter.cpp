#include "negative_filter.h"

void Negative::MakeFilter(Image& image) {
    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            RGB col = image.GetColor(j, i);
            image.SetColor(RGB(255 - col.r, 255 - col.g, 255 - col.b), j, i);
        }
    }
}
