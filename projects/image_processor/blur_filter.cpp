#include "blur_filter.h"
#include <cmath>
#include <algorithm>

void AddFrame(const std::vector<std::vector<RGB>>& old_im, std::vector<std::vector<RGB>>& new_im, const size_t i,
              const size_t pad, const size_t width) {
    for (size_t j = 0; j < pad; ++j) {
        new_im.back().push_back(old_im[i][0]);
    }

    for (size_t j = 0; j < width; ++j) {
        new_im.back().push_back(old_im[i][j]);
    }

    for (size_t j = 0; j < pad; ++j) {
        new_im.back().push_back(old_im[i][width - 1]);
    }
}

void GaussBlur::MakeFrame(const std::vector<std::vector<RGB>>& old_im, std::vector<std::vector<RGB>>& new_im) const {

    size_t height = old_im.size();
    size_t width = old_im[0].size();

    size_t pad = std::floor(sigma_ * 3);

    for (size_t i = 0; i < height + 2 * pad; ++i) {
        new_im.emplace_back();
        if (i < pad) {
            AddFrame(old_im, new_im, 0, pad, width);
        }

        if (i >= pad && i < height + pad) {
            AddFrame(old_im, new_im, i - pad, pad, width);
        }

        if (i >= pad + height && i < height + 2 * pad) {
            AddFrame(old_im, new_im, height - 1, pad, width);
        }
    }
}

void UpdCol(const RGB& n, double& upd_r, double& upd_g, double& upd_b, const ssize_t i, const ssize_t k,
            const double sigma) {
    upd_r += (static_cast<double>(n.r) / (std::sqrt(2 * M_PI * sigma * sigma))) *
             exp(static_cast<double>(-(i - k) * (i - k)) / (2 * sigma * sigma));
    upd_g += static_cast<double>(n.g) / (std::sqrt(2 * M_PI * sigma * sigma)) *
             exp(static_cast<double>(-(i - k) * (i - k)) / (2 * sigma * sigma));
    upd_b += static_cast<double>(n.b) / (std::sqrt(2 * M_PI * sigma * sigma)) *
             exp(static_cast<double>(-(i - k) * (i - k)) / (2 * sigma * sigma));
}

RGB MakeRGB(const double r, const double g, const double b) {
    int upd_r = std::max(0, std::min(255, static_cast<int>(std::round(r))));
    int upd_g = std::max(0, std::min(255, static_cast<int>(std::round(g))));
    int upd_b = std::max(0, std::min(255, static_cast<int>(std::round(b))));

    return RGB(upd_r, upd_g, upd_b);
}

void GaussBlur::MakeFilter(Image& image) {

    ssize_t pad = std::floor(sigma_ * 3);

    std::vector<std::vector<RGB>> copy;
    MakeFrame(image.data_, copy);

    for (ssize_t i = pad; i < image.height_ + pad; ++i) {
        for (ssize_t j = pad; j < image.width_ + pad; ++j) {

            double r = 0;
            double g = 0;
            double b = 0;

            for (ssize_t k = 0; k < image.width_ + 2 * pad; ++k) {
                RGB upd_col = copy[i][k];
                UpdCol(upd_col, r, g, b, j, k, sigma_);
            }

            image.SetColor(MakeRGB(r, g, b), j - pad, i - pad);
        }
    }

    copy = {};
    MakeFrame(image.data_, copy);

    for (ssize_t i = pad; i < image.height_ + pad; ++i) {
        for (ssize_t j = pad; j < image.width_ + pad; ++j) {

            double r = 0;
            double g = 0;
            double b = 0;

            for (ssize_t k = 0; k < image.height_ + 2 * pad; ++k) {
                RGB upd_col = copy[k][j];
                UpdCol(upd_col, r, g, b, i, k, sigma_);
            }

            image.SetColor(MakeRGB(r, g, b), j - pad, i - pad);
        }
    }
}
