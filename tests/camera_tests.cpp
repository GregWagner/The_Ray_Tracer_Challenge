#include <gtest/gtest.h>

#include <cmath>

#include "camera.hpp"
#include "matrix.hpp"

TEST(Camera, PixelSizeForHorizontalCanvas) {
    Camera cameraValue = camera(200, 125, PI / 2.0);

    EXPECT_NEAR(cameraValue.pixelSize, 0.01, 0.00001);
    EXPECT_NEAR(cameraValue.pixel_size, 0.01, 0.00001);
}

TEST(Camera, PixelSizeForVerticalCanvas) {
    Camera cameraValue = camera(125, 200, PI / 2.0);

    EXPECT_NEAR(cameraValue.pixelSize, 0.01, 0.00001);
    EXPECT_NEAR(cameraValue.pixel_size, 0.01, 0.00001);
}

TEST(Camera, ConstructingACamera) {
    Camera cameraValue = camera(160, 120, PI / 2.0);

    EXPECT_EQ(cameraValue.hsize, 160);
    EXPECT_EQ(cameraValue.vsize, 120);
    EXPECT_DOUBLE_EQ(cameraValue.fieldOfView, PI / 2.0);
    EXPECT_TRUE(cameraValue.transform == identityMatrix());
    EXPECT_DOUBLE_EQ(cameraValue.field_of_view, PI / 2.0);
}