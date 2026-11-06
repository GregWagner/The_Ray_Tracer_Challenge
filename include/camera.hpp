#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>

#include "canvas.hpp"
#include "matrix.hpp"
#include "ray.hpp"
#include "tuple.hpp"
#include "world.hpp"

struct Camera {
    int hsize;
    int vsize;
    double fieldOfView;
    double field_of_view;
    Matrix transform;
    double pixelSize;
    double pixel_size;
    double halfWidth;
    double half_width;
    double halfHeight;
    double half_height;

    Camera();
    Camera(int hsizeValue, int vsizeValue, double fieldOfViewValue);
};

Camera camera(int hsizeValue, int vsizeValue, double fieldOfViewValue);
Camera camera(int hsizeValue, int vsizeValue, double fieldOfViewValue, Matrix transformValue);

Ray ray_for_pixel(Camera cameraValue, int xValue, int yValue);
Ray rayForPixel(Camera cameraValue, int xValue, int yValue);

Canvas render(Camera cameraValue, World worldValue);
Canvas renderCamera(Camera cameraValue, World worldValue);
#endif
