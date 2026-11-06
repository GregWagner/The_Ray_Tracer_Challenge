#include <gtest/gtest.h>

#include <cmath>

#include "intersection.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "tuple.hpp"

TEST(Shape, DefaultMaterial) {
    TestShape shapeValue = test_shape();

    EXPECT_TRUE(shapeValue.material == material());
}

TEST(Shape, AssigningMaterial) {
    TestShape shapeValue = test_shape();
    Material materialValue = material();
    materialValue.ambient = 1.0;

    shapeValue.material = materialValue;

    EXPECT_TRUE(shapeValue.material == materialValue);
}

TEST(Shape, IntersectingScaledShape) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    TestShape shapeValue = test_shape();
    shapeValue.transform = scaling(2.0, 2.0, 2.0);

    Intersections intersectionsValue = intersect(shapeValue, rayValue);

    EXPECT_TRUE(shapeValue.saved_ray.origin == point(0.0, 0.0, -2.5));
    EXPECT_TRUE(shapeValue.saved_ray.direction == vector(0.0, 0.0, 0.5));
    EXPECT_TRUE(shapeValue.savedRay.origin == point(0.0, 0.0, -2.5));
}

TEST(Shape, IntersectingTranslatedShape) {
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    TestShape shapeValue = test_shape();
    shapeValue.transform = translation(5.0, 0.0, 0.0);

    Intersections intersectionsValue = intersect(shapeValue, rayValue);

    EXPECT_TRUE(shapeValue.saved_ray.origin == point(-5.0, 0.0, -5.0));
    EXPECT_TRUE(shapeValue.saved_ray.direction == vector(0.0, 0.0, 1.0));
}

TEST(Shape, NormalOnTranslatedShape) {
    TestShape shapeValue = test_shape();
    set_transform(shapeValue, translation(0.0, 1.0, 0.0));

    Tuple normalValue = normal_at(shapeValue, point(0.0, 1.70711, -0.70711));

    EXPECT_NEAR(normalValue.x, 0.0, 0.00001);
    EXPECT_NEAR(normalValue.y, 0.70711, 0.00001);
    EXPECT_NEAR(normalValue.z, -0.70711, 0.00001);
}

TEST(Shape, NormalOnTransformedShape) {
    double value = std::sqrt(2.0) / 2.0;
    TestShape shapeValue = test_shape();
    Matrix matrixValue = scaling(1.0, 0.5, 1.0) * rotation_z(PI / 5.0);
    set_transform(shapeValue, matrixValue);

    Tuple normalValue = normal_at(shapeValue, point(0.0, value, -value));

    EXPECT_NEAR(normalValue.x, 0.0, 0.00001);
    EXPECT_NEAR(normalValue.y, 0.97014, 0.00001);
    EXPECT_NEAR(normalValue.z, -0.24254, 0.00001);
}

TEST(Shape, DefaultTransform) {
    TestShape shapeValue = test_shape();
    EXPECT_TRUE(shapeValue.transform == identityMatrix());
}

TEST(Shape, AssigningTransform) {
    TestShape shapeValue = test_shape();
    shapeValue.transform = translation(2.0, 3.0, 4.0);
    EXPECT_TRUE(shapeValue.transform == translation(2.0, 3.0, 4.0));
}
