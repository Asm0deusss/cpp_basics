#include <catch.hpp>
#include "ImEx.h"
#include "blur_filter.h"

TEST_CASE("Blur") {
    BMP bmp_im;
    DIB dib_im;
    Image image;
    ImEx::ImportImage("../projects/image_processor/examples/example.bmp", bmp_im, dib_im, image);

    GaussBlur gauss(5);
    gauss.MakeFilter(image);

    BMP bmp_im2;
    DIB dib_im2;
    Image image2;
    ImEx::ImportImage("../projects/image_processor/examples/blur.bmp", bmp_im2, dib_im2, image2);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            RGB col1 = image.GetColor(j, i);
            RGB col2 = image2.GetColor(j, i);
            REQUIRE(abs(col1.r - col2.r) <= 5);
            REQUIRE(abs(col1.g - col2.g) <= 5);
            REQUIRE(abs(col1.b - col2.b) <= 5);
        }
    }

    bmp_im = BMP(image.width_, image.height_);
    dib_im = DIB(image.width_, image.height_);
    ImEx::ExportImage("../projects/image_processor/examples/my_blur.bmp", bmp_im, dib_im, image);
}
