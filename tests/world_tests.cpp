#include <gtest/gtest.h>

#include <algorithm>

#include "world.hpp"
#include "matrix.hpp"
#include "tuple.hpp"
#include "material.hpp"

TEST(World, CreatingWorld) {
    World worldValue = world();

    EXPECT_EQ(worldValue.objects.size(), 0);
    EXPECT_EQ(worldValue.lights.size(), 0);
    EXPECT_FALSE(worldValue.hasLight);
}

TEST(World, ShadingAnIntersection) {
    World worldValue = default_world();
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));
    Sphere &shapeValue = worldValue.objects[0];
    Intersection intersectionValue = intersection(4.0, shapeValue);

    Computation comps = prepare_computations(intersectionValue, rayValue);
    Tuple resultValue = shade_hit(worldValue, comps);

    EXPECT_NEAR(resultValue.red, 0.38066, 0.00001);
    EXPECT_NEAR(resultValue.green, 0.47583, 0.00001);
    EXPECT_NEAR(resultValue.blue, 0.2855, 0.00001);
}

TEST(World, ColorWithIntersectionBehindRay) {
    World worldValue = default_world();
    Sphere &outerValue = worldValue.objects[0];
    Sphere &innerValue = worldValue.objects[1];
    outerValue.material.ambient = 1.0;
    innerValue.material.ambient = 1.0;

    Ray rayValue = ray(point(0.0, 0.0, 0.75), vector(0.0, 0.0, -1.0));

    Tuple resultValue = color_at(worldValue, rayValue);

    EXPECT_TRUE(resultValue == innerValue.material.color);
}

TEST(World, ColorAtRayHits) {
    World worldValue = default_world();
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));

    Tuple resultValue = color_at(worldValue, rayValue);

    EXPECT_NEAR(resultValue.red, 0.38066, 0.00001);
    EXPECT_NEAR(resultValue.green, 0.47583, 0.00001);
    EXPECT_NEAR(resultValue.blue, 0.2855, 0.00001);
}

TEST(World, ShadingAnIntersectionFromTheInside) {
    World worldValue = default_world();
    worldValue.light = point_light(point(0.0, 0.25, 0.0), color(1.0, 1.0, 1.0));
    worldValue.hasLight = true;

    Ray rayValue = ray(point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0));
    Sphere &shapeValue = worldValue.objects[1];
    Intersection intersectionValue = intersection(0.5, shapeValue);

    Computation comps = prepare_computations(intersectionValue, rayValue);
    Tuple resultValue = shade_hit(worldValue, comps);

    EXPECT_NEAR(resultValue.red, 0.90498, 0.00001);
    EXPECT_NEAR(resultValue.green, 0.90498, 0.00001);
    EXPECT_NEAR(resultValue.blue, 0.90498, 0.00001);
}

TEST(World, IntersectWorldWithRay) {
    World worldValue = default_world();
    Ray rayValue = ray(point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0));

    Intersections intersectionsValue = intersect_world(worldValue, rayValue);

    EXPECT_EQ(intersectionsValue.count, 4);
    EXPECT_DOUBLE_EQ(intersectionsValue[0].t, 4.0);
    EXPECT_DOUBLE_EQ(intersectionsValue[1].t, 4.5);
    EXPECT_DOUBLE_EQ(intersectionsValue[2].t, 5.5);
    EXPECT_DOUBLE_EQ(intersectionsValue[3].t, 6.0);
}

TEST(World, DefaultWorld) {
    PointLight lightValue = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));

    Sphere sphereOne = sphere();
    sphereOne.material.color = color(0.8, 1.0, 0.6);
    sphereOne.material.diffuse = 0.7;
    sphereOne.material.specular = 0.2;

    Sphere sphereTwo = sphere();
    set_transform(sphereTwo, scaling(0.5, 0.5, 0.5));

    World worldValue = default_world();

    EXPECT_TRUE(worldValue.hasLight);
    EXPECT_TRUE(worldValue.light == lightValue);
    EXPECT_EQ(worldValue.lights.size(), 1);
    EXPECT_EQ(worldValue.objects.size(), 2);
    EXPECT_TRUE(std::find(worldValue.objects.begin(), worldValue.objects.end(), sphereOne) != worldValue.objects.end());
    EXPECT_TRUE(std::find(worldValue.objects.begin(), worldValue.objects.end(), sphereTwo) != worldValue.objects.end());
}