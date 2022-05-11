#include "my_filter.h"
#include <math.h>
#include <cmath>
#include "matrix_filter.h"

void SobelFilter::MakeFilter(Image &im) {

    Image im_x = im;
    Image im_y = im;
    MatrixFilter fil_x = MatrixFilter({{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}});

    MatrixFilter fil_y = MatrixFilter({{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}});

    fil_x.MakeFilter(im_x);
    fil_y.MakeFilter(im_y);

    for (size_t i = 0; i < im.height_; ++i) {
        for (size_t j = 0; j < im.width_; ++j) {
            RGB col_x = im_x.GetColor(j, i);
            RGB col_y = im_y.GetColor(j, i);

            int r = std::max(
                0, std::min(255, static_cast<int>(std::round(std::sqrt(col_x.r * col_x.r + col_y.r * col_y.r)))));
            int g = std::max(
                0, std::min(255, static_cast<int>(std::round(std::sqrt(col_x.g * col_x.g + col_y.g * col_y.g)))));
            int b = std::max(
                0, std::min(255, static_cast<int>(std::round(std::sqrt(col_x.b * col_x.b + col_y.b * col_y.b)))));

            im.SetColor(RGB(r, g, b), j, i);
        }
    }
}
