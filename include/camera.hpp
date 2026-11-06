#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>

#include "matrix.hpp"

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
#endif
