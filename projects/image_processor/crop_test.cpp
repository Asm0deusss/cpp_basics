#include <catch.hpp>
#include "ImEx.h"
#include "crop_filter.h"

TEST_CASE("Crop") {
    BMP bmp_im;
    DIB dib_im;
    Image image;
    ImEx::ImportImage("example.bmp", bmp_im, dib_im, image);

    Crop a(500, 500);
    a.MakeFilter(image);
    REQUIRE(image.width_ == 500);
    REQUIRE(image.height_ == 500);

    Crop b(1000, 1000);
    b.MakeFilter(image);
    REQUIRE(image.width_ == 500);
    REQUIRE(image.height_ == 500);

    bmp_im = BMP(image.width_, image.height_);
    dib_im = DIB(image.width_, image.height_);

    ImEx::ExportImage("crop_image.bmp", bmp_im, dib_im, image);
}
