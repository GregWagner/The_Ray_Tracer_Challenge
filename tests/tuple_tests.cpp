#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "lib/tuple.h"

using namespace rtc;
using Catch::Approx;

TEST_CASE("Points and vectors are distinguished by w", "[tuple]") {
    Tuple p = Tuple::point(4, -4, 3);
    Tuple v = Tuple::vector(4, -4, 3);

    REQUIRE(p.is_point());
    REQUIRE_FALSE(p.is_vector());
    REQUIRE(v.is_vector());
    REQUIRE_FALSE(v.is_point());
}

TEST_CASE("Magnitude and normalization", "[tuple]") {
    Tuple v = Tuple::vector(1, 2, 3);
    REQUIRE(magnitude(v) == Approx(std::sqrt(14.0)));

    Tuple n = normalize(v);
    REQUIRE(n == Tuple(1 / std::sqrt(14.0), 2 / std::sqrt(14.0), 3 / std::sqrt(14.0), 0.0));
}

