#include "crop_filter.h"

void Crop::MakeFilter(Image& image) {
    if (height_ == 0 || width_ == 0) {
        throw std::runtime_error("Bad size for crop");
    }

    if (height_ < image.height_) {
        image.data_.erase(image.data_.begin(), image.data_.begin() + (image.height_ - height_));
        image.height_ = height_;
    }

    if (width_ < image.width_) {
        for (size_t i = 0; i < image.height_; ++i) {
            image.data_[i].resize(width_);
        }
        image.width_ = width_;
    }
}
