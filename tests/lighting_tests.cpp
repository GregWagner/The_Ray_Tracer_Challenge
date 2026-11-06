#include <gtest/gtest.h>

#include <cmath>

#include "lighting.hpp"
#include "material.hpp"
#include "tuple.hpp"

TEST(Lighting, EyeBetweenLightAndSurface) {
    Material materialValue = material();
    Tuple positionValue = point(0.0, 0.0, 0.0);
    Tuple eyevValue = vector(0.0, 0.0, -1.0);
    Tuple normalvValue = vector(0.0, 0.0, -1.0);
    PointLight lightValue = point_light(point(0.0, 0.0, -10.0), color(1.0, 1.0, 1.0));

    Tuple resultValue = lighting(materialValue, lightValue, positionValue, eyevValue, normalvValue);

    EXPECT_NEAR(resultValue.red, 1.9, 0.00001);
    EXPECT_NEAR(resultValue.green, 1.9, 0.00001);
    EXPECT_NEAR(resultValue.blue, 1.9, 0.00001);
}

TEST(Lighting, EyeOffset45Degrees) {
    Material materialValue = material();
    Tuple positionValue = point(0.0, 0.0, 0.0);
    double value = std::sqrt(2.0) / 2.0;
    Tuple eyevValue = vector(0.0, value, -value);
    Tuple normalvValue = vector(0.0, 0.0, -1.0);
    PointLight lightValue = point_light(point(0.0, 0.0, -10.0), color(1.0, 1.0, 1.0));

    Tuple resultValue = lighting(materialValue, lightValue, positionValue, eyevValue, normalvValue);

    EXPECT_TRUE(resultValue == color(1.0, 1.0, 1.0));
}