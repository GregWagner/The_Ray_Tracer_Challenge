#include <gtest/gtest.h>

#include "world.hpp"

TEST(World, CreatingWorld) {
    World worldValue = world();

    EXPECT_EQ(worldValue.objects.size(), 0);
    EXPECT_EQ(worldValue.lights.size(), 0);
}