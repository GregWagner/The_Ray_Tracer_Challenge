#include <gtest/gtest.h>

#include "point_light.hpp"
#include "tuple.hpp"

TEST(PointLight, PointLightHasPositionAndIntensity) {
    Tuple intensityValue = color(1.0, 1.0, 1.0);
    Tuple positionValue = point(0.0, 0.0, 0.0);

    PointLight lightValue = point_light(positionValue, intensityValue);

    EXPECT_TRUE(lightValue.position == positionValue);
    EXPECT_TRUE(lightValue.intensity == intensityValue);
}