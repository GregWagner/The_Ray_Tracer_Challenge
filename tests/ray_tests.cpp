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

TEST(Ray, ComputingAPointFromADistance) {
    Ray rayValue = ray(point(2.0, 3.0, 4.0), vector(1.0, 0.0, 0.0));

    EXPECT_TRUE(position(rayValue, 0.0) == point(2.0, 3.0, 4.0));
    EXPECT_TRUE(position(rayValue, 1.0) == point(3.0, 3.0, 4.0));
    EXPECT_TRUE(position(rayValue, -1.0) == point(1.0, 3.0, 4.0));
    EXPECT_TRUE(position(rayValue, 2.5) == point(4.5, 3.0, 4.0));
}