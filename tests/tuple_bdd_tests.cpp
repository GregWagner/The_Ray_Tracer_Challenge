#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "lib/tuple.h"

using namespace rtc;
using Catch::Approx;

SCENARIO("Points and vectors are distinguished by w", "[tuple][bdd]")
{
    GIVEN("a point created with Tuple::point and a vector created with Tuple::vector")
    {
        Tuple p = Tuple::point(4, -4, 3);
        Tuple v = Tuple::vector(4, -4, 3);

        THEN("the point and vector predicates are correct")
        {
            REQUIRE(p.is_point());
            REQUIRE_FALSE(p.is_vector());
            REQUIRE(v.is_vector());
            REQUIRE_FALSE(v.is_point());
        }
    }
}

SCENARIO("Magnitude and normalization", "[tuple][bdd]")
{
    GIVEN("a vector (1,2,3)")
    {
        Tuple v = Tuple::vector(1, 2, 3);

        WHEN("magnitude is computed")
        {
            THEN("it equals sqrt(14)")
            {
                REQUIRE(magnitude(v) == Approx(std::sqrt(14.0)));
            }
        }

        WHEN("the vector is normalized")
        {
            Tuple n = normalize(v);
            THEN("the result is the normalized vector")
            {
                REQUIRE(n == Tuple(1 / std::sqrt(14.0), 2 / std::sqrt(14.0), 3 / std::sqrt(14.0), 0.0));
            }
        }
    }
}
