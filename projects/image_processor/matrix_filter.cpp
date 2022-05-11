#include "matrix_filter.h"

void MatrixFilter::MakeNewImage(const std::vector<std::vector<RGB>>& old_im, std::vector<std::vector<RGB>>& new_im) {

    size_t pad = matrix_.size() / 2;

    size_t height = old_im.size();
    size_t width = old_im[0].size();

    for (size_t i = 0; i < width + 2 * pad; ++i) {
        new_im.push_back({});
        if (i < pad) {
            for (size_t j = 0; j < pad; ++j) {
                new_im.back().push_back(old_im[0][0]);
            }

            for (size_t j = 0; j < width; ++j) {
                new_im.back().push_back(old_im[0][j]);
            }

            for (size_t j = 0; j < pad; ++j) {
                new_im.back().push_back(old_im[0][width - 1]);
            }
        }

        if (i >= pad && i < height + pad) {
            for (size_t j = 0; j < pad; j++) {
                new_im.back().push_back(old_im[i - pad][0]);
            }

            for (size_t j = 0; j < width; j++) {
                new_im.back().push_back(old_im[i - pad][j]);
            }

            for (size_t j = 0; j < pad; j++) {
                new_im.back().push_back(old_im[i - pad][width - 1]);
            }
        }

        if (i >= pad + height && i < height + 2 * pad) {
            for (size_t j = 0; j < pad; ++j) {
                new_im.back().push_back(old_im[height - 1][0]);
            }

            for (size_t j = 0; j < width; ++j) {
                new_im.back().push_back(old_im[height - 1][j]);
            }

            for (size_t j = 0; j < pad; ++j) {
                new_im.back().push_back(old_im[height - 1][width - 1]);
            }
        }
    }
}

void MatrixFilter::MakeFilter(Image& im) {
    size_t pad = matrix_.size() / 2;

    std::vector<std::vector<RGB>> im_copy;
    MakeNewImage(im.data_, im_copy);
    for (size_t i = pad; i < im.height_ + pad; ++i) {
        for (size_t j = pad; j < im.width_ + pad; ++j) {
            ssize_t r = 0;
            ssize_t g = 0;
            ssize_t b = 0;

            for (size_t k = 0; k < matrix_.size(); ++k) {
                for (size_t m = 0; m < matrix_[0].size(); ++m) {
                    r += matrix_[k][m] * im_copy[i - pad + k][j - pad + m].r;
                    g += matrix_[k][m] * im_copy[i - pad + k][j - pad + m].g;
                    b += matrix_[k][m] * im_copy[i - pad + k][j - pad + m].b;
                }
            }

            r = std::max(static_cast<ssize_t>(0), std::min(static_cast<ssize_t>(255), r));
            g = std::max(static_cast<ssize_t>(0), std::min(static_cast<ssize_t>(255), g));
            b = std::max(static_cast<ssize_t>(0), std::min(static_cast<ssize_t>(255), b));

            im.SetColor(RGB(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b)), j - pad, i - pad);
        }
    }
}
