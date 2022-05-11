#include <catch.hpp>
#include <palindrome.h>

TEST_CASE("IsPalindrome") {
    REQUIRE(IsPalindrome("abba"));

    REQUIRE(!IsPalindrome("qwerty"));
}
