#include "edge_detection_filter.h"

void EdgeDetection::MakeFilter(Image& im) {

    GrayScale::MakeFilter(im);

    MatrixFilter::MakeFilter(im);

    for (auto& row : im.data_) {
        for (auto& pix : row) {
            if (static_cast<float>(pix.r) > par_ * 255.0f) {
                pix = RGB(255, 255, 255);
            } else {
                pix = RGB(0, 0, 0);
            }
        }
    }
}
