#include <gtest/gtest.h>

#include "intersection.hpp"
#include "ray.hpp"
#include "tuple.hpp"

TEST(Sphere, AggregatingIntersections) {
    Sphere sphereValue = sphere();
    Intersection intersectionOne = intersection(1.0, sphereValue);
    Intersection intersectionTwo = intersection(2.0, sphereValue);

    Intersections intersectionsValue = intersections(intersectionOne, intersectionTwo);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_DOUBLE_EQ(intersectionsValue[0].t, 1.0);
    EXPECT_DOUBLE_EQ(intersectionsValue[1].t, 2.0);
}

TEST(Sphere, IntersectionEncapsulatesTAndObject) {
    Sphere sphereValue = sphere();

    Intersection intersectionValue = intersection(3.5, sphereValue);

    EXPECT_DOUBLE_EQ(intersectionValue.t, 3.5);
    EXPECT_EQ(intersectionValue.object, &sphereValue);
}

TEST(Sphere, IntersectSetsObjectOnIntersection) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_EQ(intersectionsValue[0].object, &sphereValue);
    EXPECT_EQ(intersectionsValue[1].object, &sphereValue);
}

TEST(Sphere, RayIntersectsSphereAtTwoPoints) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_DOUBLE_EQ(intersectionsValue[0], 4.0);
    EXPECT_DOUBLE_EQ(intersectionsValue[1], 6.0);
}

TEST(Sphere, RayOriginatesInsideSphere) {
    Ray rayValue = ray(point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_DOUBLE_EQ(intersectionsValue[0], -1.0);
    EXPECT_DOUBLE_EQ(intersectionsValue[1], 1.0);
}

TEST(Sphere, SphereBehindRay) {
    Ray rayValue = ray(point(0.0, 0.0, 5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_DOUBLE_EQ(intersectionsValue[0], -6.0);
    EXPECT_DOUBLE_EQ(intersectionsValue[1], -4.0);
}

TEST(Sphere, RayMissesSphere) {
    Ray rayValue = ray(point(0.0, 2.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 0);
}

TEST(Sphere, RayIntersectsSphereAtTangent) {
    Ray rayValue = ray(point(0.0, 1.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_DOUBLE_EQ(intersectionsValue[0], 5.0);
    EXPECT_DOUBLE_EQ(intersectionsValue[1], 5.0);
}