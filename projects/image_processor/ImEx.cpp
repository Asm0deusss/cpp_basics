#include "ImEx.h"

void ImEx::ImportImage(const char *path, BMP &bmp, DIB &dib, Image &cur_image) {
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("You can't open this file");
    }

    file.read(reinterpret_cast<char *>(bmp.data), BMP_HEAD_SIZE);

    if (bmp[0] != 'B' || bmp[1] != 'M') {
        file.close();
        throw std::runtime_error("Wrong file type");
    }

    file.read(reinterpret_cast<char *>(dib.data), DIB_HEAD_SIZE);

    size_t width = dib.GetWidth();
    size_t height = dib.GetHeight();
    cur_image.width_ = width;
    cur_image.height_ = height;

    char padding = (OVERALL_BYTES - (cur_image.width_ * BYTES_FOR_COLOR) % OVERALL_BYTES) % OVERALL_BYTES;
    cur_image.data_.reserve(height);

    // Filling image.data with RGB colors
    for (size_t i = 0; i < height; ++i) {
        cur_image.data_.push_back({});
        cur_image.data_.back().reserve(width);
        for (size_t j = 0; j < width; ++j) {
            unsigned char read_memo[BYTES_FOR_COLOR];
            file.read(reinterpret_cast<char *>(read_memo), BYTES_FOR_COLOR);
            RGB color;
            color.r = read_memo[2];
            color.g = read_memo[1];
            color.b = read_memo[0];
            cur_image.data_.back().push_back(color);
        }
        file.ignore(padding);
    }
    file.close();
}
void ImEx::ExportImage(const char *path, BMP &bmp, DIB &dip, Image &cur_image) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("You can't open this file");
    }

    char padding = (OVERALL_BYTES - (cur_image.width_ * BYTES_FOR_COLOR) % OVERALL_BYTES) % OVERALL_BYTES;
    char pad[BYTES_FOR_COLOR] = {0, 0, 0};
    file.write(reinterpret_cast<char *>(bmp.data), BMP_HEAD_SIZE);
    file.write(reinterpret_cast<char *>(dip.data), DIB_HEAD_SIZE);

    // Writing color of pixels
    for (size_t i = 0; i < cur_image.height_; ++i) {
        for (size_t j = 0; j < cur_image.width_; ++j) {
            char r = cur_image.GetColor(j, i).r;
            char g = cur_image.GetColor(j, i).g;
            char b = cur_image.GetColor(j, i).b;
            char col[BYTES_FOR_COLOR] = {b, g, r};
            file.write(reinterpret_cast<char *>(col), BYTES_FOR_COLOR);
        }
        file.write(reinterpret_cast<char *>(pad), padding);
    }

    file.close();
}
