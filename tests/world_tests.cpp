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

TEST(World, DefaultWorld) {
    PointLight lightValue = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));

    Sphere sphereOne = sphere();
    sphereOne.material.color = color(0.8, 1.0, 0.6);
    sphereOne.material.diffuse = 0.7;
    sphereOne.material.specular = 0.2;

    Sphere sphereTwo = sphere();
    set_transform(sphereTwo, scaling(0.5, 0.5, 0.5));
    sphereTwo.material.color = color(0.8, 1.0, 0.6);
    sphereTwo.material.diffuse = 0.7;
    sphereTwo.material.specular = 0.2;

    World worldValue = default_world();

    EXPECT_TRUE(worldValue.hasLight);
    EXPECT_TRUE(worldValue.light == lightValue);
    EXPECT_EQ(worldValue.lights.size(), 1);
    EXPECT_EQ(worldValue.objects.size(), 2);
    EXPECT_TRUE(std::find(worldValue.objects.begin(), worldValue.objects.end(), sphereOne) != worldValue.objects.end());
    EXPECT_TRUE(std::find(worldValue.objects.begin(), worldValue.objects.end(), sphereTwo) != worldValue.objects.end());
}