#include <catch.hpp>
#include "ImEx.h"
#include "edge_detection_filter.h"

TEST_CASE("Edge detection") {
    BMP bmp_im;
    DIB dib_im;
    Image image;
    ImEx::ImportImage("../projects/image_processor/examples/example.bmp", bmp_im, dib_im, image);

    EdgeDetection edge(1);
    edge.MakeFilter(image);

    for (size_t i = 0; i < image.height_; ++i) {
        for (size_t j = 0; j < image.width_; ++j) {
            RGB col = image.GetColor(j, i);
            REQUIRE(col.r == 0);
            REQUIRE(col.g == 0);
            REQUIRE(col.b == 0);
        }
    }
}
