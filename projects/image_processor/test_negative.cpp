#include <catch.hpp>
#include "ImEx.h"
#include "negative_filter.h"

TEST_CASE("Negative") {
    BMP bmp_im;
    DIB dib_im;
    Image image;
    ImEx::ImportImage("../projects/image_processor/examples/example.bmp", bmp_im, dib_im, image);

    Negative a = Negative();
    a.MakeFilter(image);

    BMP bmp_im2;
    DIB dib_im2;
    Image image2;
    ImEx::ImportImage("../projects/image_processor/examples/negative.bmp", bmp_im2, dib_im2, image2);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            REQUIRE(image.GetColor(j, i).r == image2.GetColor(j, i).r);
            REQUIRE(image.GetColor(j, i).g == image2.GetColor(j, i).g);
            REQUIRE(image.GetColor(j, i).b == image2.GetColor(j, i).b);
        }
    }

    bmp_im = BMP(image.width_, image.height_);
    dib_im = DIB(image.width_, image.height_);
    ImEx::ExportImage("../projects/image_processor/examples/my_negative.bmp", bmp_im, dib_im, image);
}
