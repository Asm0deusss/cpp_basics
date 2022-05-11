#include <catch.hpp>

#include "zip.h"

#include <forward_list>
#include <sstream>

TEST_CASE("Zip2") {
    const int a[]{1, 2, 3, 4};
    const std::forward_list<std::string> b = {"one", "two", "three"};
    std::stringstream stream;

    for (const auto& [first, second] : Zip(a, b)) {
        stream << first << ":" << second << " ";
    }

    REQUIRE("1:one 2:two 3:three " == stream.str());
}
