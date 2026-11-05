#include <gtest/gtest.h>

#include "material.hpp"
#include "tuple.hpp"

TEST(Material, DefaultMaterial) {
    Material materialValue = material();

    EXPECT_TRUE(materialValue.color == color(1.0, 1.0, 1.0));
    EXPECT_DOUBLE_EQ(materialValue.ambient, 0.1);
    EXPECT_DOUBLE_EQ(materialValue.diffuse, 0.9);
    EXPECT_DOUBLE_EQ(materialValue.specular, 0.9);
    EXPECT_DOUBLE_EQ(materialValue.shininess, 200.0);
}