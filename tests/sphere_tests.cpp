#include <gtest/gtest.h>

#include <cmath>

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

TEST(Sphere, HitWhenAllIntersectionsPositive) {
    Sphere sphereValue = sphere();
    Intersection intersectionOne = intersection(1.0, sphereValue);
    Intersection intersectionTwo = intersection(2.0, sphereValue);
    Intersections intersectionsValue = intersections(intersectionTwo, intersectionOne);

    Hit hitValue = hit(intersectionsValue);

    EXPECT_TRUE(hitValue);
    EXPECT_TRUE(hitValue == intersectionOne);
}

TEST(Sphere, HitWhenSomeIntersectionsNegative) {
    Sphere sphereValue = sphere();
    Intersection intersectionOne = intersection(-1.0, sphereValue);
    Intersection intersectionTwo = intersection(1.0, sphereValue);
    Intersections intersectionsValue = intersections(intersectionTwo, intersectionOne);

    Hit hitValue = hit(intersectionsValue);

    EXPECT_TRUE(hitValue);
    EXPECT_TRUE(hitValue == intersectionTwo);
}

TEST(Sphere, HitWhenAllIntersectionsNegative) {
    Sphere sphereValue = sphere();
    Intersection intersectionOne = intersection(-2.0, sphereValue);
    Intersection intersectionTwo = intersection(-1.0, sphereValue);
    Intersections intersectionsValue = intersections(intersectionTwo, intersectionOne);

    Hit hitValue = hit(intersectionsValue);

    EXPECT_FALSE(hitValue);
}

TEST(Sphere, HitIsLowestNonnegativeIntersection) {
    Sphere sphereValue = sphere();
    Intersection intersectionOne = intersection(5.0, sphereValue);
    Intersection intersectionTwo = intersection(7.0, sphereValue);
    Intersection intersectionThree = intersection(-3.0, sphereValue);
    Intersection intersectionFour = intersection(2.0, sphereValue);
    Intersections intersectionsValue = intersections(intersectionOne, intersectionTwo, intersectionThree, intersectionFour);

    Hit hitValue = hit(intersectionsValue);

    EXPECT_TRUE(hitValue);
    EXPECT_TRUE(hitValue == intersectionFour);
}

TEST(Computations, PrecomputingIntersectionState) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();
    Intersection intersectionValue = intersection(4.0, sphereValue);

    Computation comps = prepare_computations(intersectionValue, rayValue);

    EXPECT_DOUBLE_EQ(comps.t, 4.0);
    EXPECT_EQ(comps.object, &sphereValue);
    EXPECT_TRUE(comps.point == point(0.0, 0.0, -1.0));
    EXPECT_TRUE(comps.eyev == vector(0.0, 0.0, -1.0));
    EXPECT_TRUE(comps.normalv == vector(0.0, 0.0, -1.0));
}

TEST(Sphere, IntersectSetsObjectOnIntersection) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_EQ(intersectionsValue[0].object, &sphereValue);
    EXPECT_EQ(intersectionsValue[1].object, &sphereValue);
}

TEST(Sphere, DefaultSphereTransformation) {
    Sphere sphereValue = sphere();

    EXPECT_TRUE(sphereValue.transform == identityMatrix());
}

TEST(Sphere, ChangingSphereTransformation) {
    Sphere sphereValue = sphere();
    Matrix transformValue = translation(2.0, 3.0, 4.0);

    set_transform(sphereValue, transformValue);

    EXPECT_TRUE(sphereValue.transform == transformValue);
}

TEST(Sphere, IntersectingScaledSphereWithRay) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();
    set_transform(sphereValue, scaling(2.0, 2.0, 2.0));

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 2);
    EXPECT_DOUBLE_EQ(intersectionsValue[0].t, 3.0);
    EXPECT_DOUBLE_EQ(intersectionsValue[1].t, 7.0);
}

TEST(Sphere, IntersectingTranslatedSphereWithRay) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere sphereValue = sphere();
    set_transform(sphereValue, translation(5.0, 0.0, 0.0));

    Intersections intersectionsValue = intersect(sphereValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 0);
}

TEST(Sphere, NormalOnSphereAtAxialPointX) {
    Sphere sphereValue = sphere();
    Tuple normalValue = normal_at(sphereValue, point(1.0, 0.0, 0.0));
    EXPECT_TRUE(normalValue == vector(1.0, 0.0, 0.0));
}

TEST(Sphere, NormalOnSphereAtAxialPointY) {
    Sphere sphereValue = sphere();
    Tuple normalValue = normal_at(sphereValue, point(0.0, 1.0, 0.0));
    EXPECT_TRUE(normalValue == vector(0.0, 1.0, 0.0));
}

TEST(Sphere, NormalOnSphereAtAxialPointZ) {
    Sphere sphereValue = sphere();
    Tuple normalValue = normal_at(sphereValue, point(0.0, 0.0, 1.0));
    EXPECT_TRUE(normalValue == vector(0.0, 0.0, 1.0));
}

TEST(Sphere, NormalOnTranslatedSphere) {
    Sphere sphereValue = sphere();
    set_transform(sphereValue, translation(0.0, 1.0, 0.0));

    Tuple normalValue = normal_at(sphereValue, point(0.0, 1.70711, -0.70711));

    EXPECT_NEAR(normalValue.x, 0.0, 0.00001);
    EXPECT_NEAR(normalValue.y, 0.70711, 0.00001);
    EXPECT_NEAR(normalValue.z, -0.70711, 0.00001);
}

TEST(Sphere, NormalOnTransformedSphere) {
    double value = std::sqrt(2.0) / 2.0;
    Matrix matrixValue = scaling(1.0, 0.5, 1.0) * rotation_z(PI / 5.0);
    Sphere sphereValue = sphere();
    set_transform(sphereValue, matrixValue);

    Tuple normalValue = normal_at(sphereValue, point(0.0, value, -value));

    EXPECT_NEAR(normalValue.x, 0.0, 0.00001);
    EXPECT_NEAR(normalValue.y, 0.97014, 0.00001);
    EXPECT_NEAR(normalValue.z, -0.24254, 0.00001);
}

TEST(Sphere, NormalIsNormalizedVector) {
    double coordinateValue = std::sqrt(3.0) / 3.0;
    Sphere sphereValue = sphere();
    Tuple normalValue = normal_at(sphereValue, point(coordinateValue, coordinateValue, coordinateValue));

    EXPECT_TRUE(normalValue == normalize(normalValue));
}

TEST(Sphere, NormalOnSphereAtNonaxialPoint) {
    double coordinateValue = std::sqrt(3.0) / 3.0;
    Sphere sphereValue = sphere();
    Tuple normalValue = normal_at(sphereValue, point(coordinateValue, coordinateValue, coordinateValue));
    EXPECT_TRUE(normalValue == vector(coordinateValue, coordinateValue, coordinateValue));
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