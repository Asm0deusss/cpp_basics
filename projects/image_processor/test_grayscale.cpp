#include <catch.hpp>
#include "ImEx.h"
#include "grayscale_filter.h"

TEST_CASE("GrayScale") {
    BMP bmp_im;
    DIB dib_im;
    Image image;
    ImEx::ImportImage("../projects/image_processor/examples/example.bmp", bmp_im, dib_im, image);

    GrayScale a;
    a.MakeFilter(image);

    BMP bmp_im2;
    DIB dib_im2;
    Image image2;
    ImEx::ImportImage("../projects/image_processor/examples/grayscale.bmp", bmp_im2, dib_im2, image2);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            REQUIRE(abs(image.GetColor(j, i).r - image2.GetColor(j, i).r) <= 5);
        }
    }

    bmp_im = BMP(image.width_, image.height_);
    dib_im = DIB(image.width_, image.height_);
    ImEx::ExportImage("../projects/image_processor/examples/my_grayscale.bmp", bmp_im, dib_im, image);
}
