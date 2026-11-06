#include <gtest/gtest.h>

#include <cmath>

#include "camera.hpp"
#include "matrix.hpp"

TEST(Camera, ConstructingACamera) {
    Camera cameraValue = camera(160, 120, PI / 2.0);

    EXPECT_EQ(cameraValue.hsize, 160);
    EXPECT_EQ(cameraValue.vsize, 120);
    EXPECT_DOUBLE_EQ(cameraValue.fieldOfView, PI / 2.0);
    EXPECT_TRUE(cameraValue.transform == identityMatrix());
    EXPECT_DOUBLE_EQ(cameraValue.field_of_view, PI / 2.0);
}