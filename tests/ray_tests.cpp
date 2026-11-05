#include <gtest/gtest.h>

#include "ray.hpp"
#include "tuple.hpp"

TEST(Ray, CreatingAndQueryingARay) {
    Tuple originValue = point(1.0, 2.0, 3.0);
    Tuple directionValue = vector(4.0, 5.0, 6.0);

    Ray rayValue = ray(originValue, directionValue);

    EXPECT_TRUE(rayValue.origin == originValue);
    EXPECT_TRUE(rayValue.direction == directionValue);
}