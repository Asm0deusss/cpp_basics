#include "grayscale_filter.h"
#include <math.h>
void GrayScale::MakeFilter(Image& image) {
    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            RGB col = image.GetColor(j, i);
            double upd_col = col.r * 0.299 + col.g * 0.587 + col.b * 0.114;

            int norm_upd_col = round(std::max(static_cast<double>(0), std::min(static_cast<double>(255), upd_col)));

            image.SetColor(RGB(norm_upd_col, norm_upd_col, norm_upd_col), j, i);
        }
    }
}
