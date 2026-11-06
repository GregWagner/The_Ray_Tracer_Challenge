#include <gtest/gtest.h>

#include <cmath>

#include "intersection.hpp"
#include "plane.hpp"
#include "tuple.hpp"

TEST(Plane, IntersectWithParallelRay) {
    Plane planeValue = plane();
    Ray rayValue = ray(point(0.0, 10.0, 0.0), vector(0.0, 0.0, 1.0));

    Intersections intersectionsValue = local_intersect(planeValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 0);
}

TEST(Plane, IntersectWithCoplanarRay) {
    Plane planeValue = plane();
    Ray rayValue = ray(point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0));

    Intersections intersectionsValue = local_intersect(planeValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 0);
}

TEST(Plane, NormalIsConstantEverywhere) {
    Plane planeValue = plane();

    Tuple normalOne = normal_at(planeValue, point(0.0, 0.0, 0.0));
    Tuple normalTwo = normal_at(planeValue, point(10.0, 0.0, -10.0));
    Tuple normalThree = normal_at(planeValue, point(-5.0, 0.0, 150.0));

    EXPECT_TRUE(normalOne == vector(0.0, 1.0, 0.0));
    EXPECT_TRUE(normalTwo == vector(0.0, 1.0, 0.0));
    EXPECT_TRUE(normalThree == vector(0.0, 1.0, 0.0));
}