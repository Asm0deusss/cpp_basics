#include <catch.hpp>
#include "ImEx.h"
#include "matrix_filter.h"

TEST_CASE("Matrix filter") {
    BMP bmp_im;
    DIB dib_im;
    Image image;
    ImEx::ImportImage("../projects/image_processor/examples/example.bmp", bmp_im, dib_im, image);

    std::vector<std::vector<RGB>> copy = image.data_;

    MatrixFilter mat({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}});
    mat.MakeFilter(image);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            RGB col1 = image.GetColor(j, i);
            RGB col2 = copy[i][j];

            REQUIRE(col1.r == col2.r);
            REQUIRE(col1.g == col2.g);
            REQUIRE(col1.b == col2.b);
        }
    }

    ImEx::ExportImage("../projects/image_processor/examples/matrix_filter.bmp", bmp_im, dib_im, image);
}
