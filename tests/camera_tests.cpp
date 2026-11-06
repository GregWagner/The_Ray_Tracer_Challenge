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

TEST(Camera, RayThroughCenterOfCanvas) {
    Camera cameraValue = camera(201, 101, PI / 2.0);

    Ray rayValue = ray_for_pixel(cameraValue, 100, 50);

    EXPECT_TRUE(rayValue.origin == point(0.0, 0.0, 0.0));
    EXPECT_TRUE(rayValue.direction == vector(0.0, 0.0, -1.0));
}

TEST(Camera, RayThroughCornerOfCanvas) {
    Camera cameraValue = camera(201, 101, PI / 2.0);

    Ray rayValue = ray_for_pixel(cameraValue, 0, 0);

    EXPECT_TRUE(rayValue.origin == point(0.0, 0.0, 0.0));
    EXPECT_NEAR(rayValue.direction.x, 0.66519, 0.00001);
    EXPECT_NEAR(rayValue.direction.y, 0.33259, 0.00001);
    EXPECT_NEAR(rayValue.direction.z, -0.66851, 0.00001);
}

TEST(Camera, RayWhenCameraTransformed) {
    Camera cameraValue = camera(201, 101, PI / 2.0);
    Matrix transformValue = rotation_y(PI / 4.0) * translation(0.0, -2.0, 5.0);
    cameraValue.transform = transformValue;

    Ray rayValue = ray_for_pixel(cameraValue, 100, 50);

    EXPECT_NEAR(rayValue.origin.x, 0.0, 0.00001);
    EXPECT_NEAR(rayValue.origin.y, 2.0, 0.00001);
    EXPECT_NEAR(rayValue.origin.z, -5.0, 0.00001);

    double rootTwoOverTwo = std::sqrt(2.0) / 2.0;
    EXPECT_NEAR(rayValue.direction.x, rootTwoOverTwo, 0.00001);
    EXPECT_NEAR(rayValue.direction.y, 0.0, 0.00001);
    EXPECT_NEAR(rayValue.direction.z, -rootTwoOverTwo, 0.00001);
}

TEST(Camera, RenderingWorldWithCamera) {
    World worldValue = default_world();
    Camera cameraValue = camera(11, 11, PI / 2.0);
    Tuple fromValue = point(0.0, 0.0, -5.0);
    Tuple toValue = point(0.0, 0.0, 0.0);
    Tuple upValue = vector(0.0, 1.0, 0.0);
    cameraValue.transform = view_transform(fromValue, toValue, upValue);

    Canvas imageValue = render(cameraValue, worldValue);

    EXPECT_TRUE(pixel_at(imageValue, 5, 5) == color(0.38066, 0.47583, 0.2855));
}

TEST(Camera, ConstructingACamera) {
    Camera cameraValue = camera(160, 120, PI / 2.0);

    EXPECT_EQ(cameraValue.hsize, 160);
    EXPECT_EQ(cameraValue.vsize, 120);
    EXPECT_DOUBLE_EQ(cameraValue.fieldOfView, PI / 2.0);
    EXPECT_TRUE(cameraValue.transform == identityMatrix());
    EXPECT_DOUBLE_EQ(cameraValue.field_of_view, PI / 2.0);
}