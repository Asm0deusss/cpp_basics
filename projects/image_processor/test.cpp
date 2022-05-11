#include <catch.hpp>
#include "ImEx.h"

void RequireRGB(RGB actual, RGB expected) {
    REQUIRE(actual.r == expected.r);
    REQUIRE(actual.g == expected.g);
    REQUIRE(actual.b == expected.b);
}

TEST_CASE("RGB struct") {
    RGB rgb = RGB();
    RequireRGB(rgb, RGB(0, 0, 0));

    RGB rgb1 = RGB(1, 2, 3);
    RequireRGB(rgb1, RGB(1, 2, 3));
}

TEST_CASE("Image struct") {
    // GetColor values
    RGB def_color = RGB();
    Image image(2, 2);
    RGB zero_color = image.GetColor(0, 0);

    RequireRGB(zero_color, def_color);

    // GetColor exceptions
    try {
        image.GetColor(100, 100);
        throw std::runtime_error("Exception check");
    } catch (std::runtime_error exception) {
        REQUIRE(exception.what() == std::string("Out of range"));
    }

    try {
        image.GetColor(-1, 0);
        throw std::runtime_error("Exception check");
    } catch (std::runtime_error exception) {
        REQUIRE(exception.what() == std::string("Out of range"));
    }

    // SetColor
    RGB new_color = RGB(1, 1, 1);
    image.SetColor(new_color, 0, 1);
    RGB get_new_color = image.GetColor(0, 1);

    RequireRGB(get_new_color, new_color);

    // Image size exceptions
    try {
        Image zero_image(0, 10);
        throw std::runtime_error("Exception check");
    } catch (std::runtime_error exception) {
        REQUIRE(exception.what() == std::string("Bad size"));
    }

    try {
        Image zero_image(100, 0);
        throw std::runtime_error("Exception check");
    } catch (std::runtime_error exception) {
        REQUIRE(exception.what() == std::string("Bad size"));
    }
}

TEST_CASE("DIB size") {
    DIB test1 = DIB(10, 100);
    REQUIRE(test1.GetWidth() == 10);
    REQUIRE(test1.GetHeight() == 100);

    DIB test2 = DIB(10000, 999999);
    REQUIRE(test2.GetWidth() == 10000);
    REQUIRE(test2.GetHeight() == 999999);
}

TEST_CASE("Import & Export") {
    BMP bmp_im1;
    DIB dib_im1;
    Image image1;
    ImEx::ImportImage("../projects/image_processor/examples/red_sq.bmp", bmp_im1, dib_im1, image1);
    ImEx::ExportImage("../projects/image_processor/examples/new_red_sq.bmp", bmp_im1, dib_im1, image1);

    BMP bmp_im2;
    DIB dib_im2;
    Image image2;
    ImEx::ImportImage("../projects/image_processor/examples/new_red_sq.bmp", bmp_im2, dib_im2, image2);

    REQUIRE(image1.width_ == image2.width_);
    REQUIRE(image1.height_ == image2.height_);

    for (size_t i = 0; i < image1.height_; ++i) {
        for (size_t j = 0; j < image1.width_; ++j) {
            RequireRGB(image1.GetColor(j, i), image2.GetColor(j, i));
        }
    }

    BMP bmp_im3;
    DIB dib_im3;
    Image image3;
    try {
        ImEx::ImportImage("../projects/image_processor/examples/none_exist_file.bmp", bmp_im3, dib_im3, image3);
        throw std::runtime_error("Exception check");
    } catch (std::runtime_error exception) {
        REQUIRE(exception.what() == std::string("You can't open this file"));
    }

    BMP bmp_im4;
    DIB dib_im4;
    Image image4;
    try {
        ImEx::ImportImage("../projects/image_processor/examples/text.txt", bmp_im4, dib_im4, image4);
        throw std::runtime_error("Exception check");
    } catch (std::runtime_error exception) {
        REQUIRE(exception.what() == std::string("Wrong file type"));
    }
}
