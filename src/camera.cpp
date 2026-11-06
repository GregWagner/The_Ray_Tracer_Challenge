#include "camera.hpp"

Camera::Camera() {
    hsize = 0;
    vsize = 0;
    fieldOfView = 0.0;
    field_of_view = 0.0;
    transform = identityMatrix();
    pixelSize = 0.0;
    pixel_size = 0.0;
    halfWidth = 0.0;
    half_width = 0.0;
    halfHeight = 0.0;
    half_height = 0.0;
}

Camera::Camera(int hsizeValue, int vsizeValue, double fieldOfViewValue) {
    hsize = hsizeValue;
    vsize = vsizeValue;
    fieldOfView = fieldOfViewValue;
    field_of_view = fieldOfViewValue;
    transform = identityMatrix();

    double halfView = std::tan(fieldOfViewValue / 2.0);
    double aspect = static_cast<double>(hsizeValue) / static_cast<double>(vsizeValue);

    if (aspect >= 1.0) {
        halfWidth = halfView;
        halfHeight = halfView / aspect;
    } else {
        halfWidth = halfView * aspect;
        halfHeight = halfView;
    }

    pixelSize = (halfWidth * 2.0) / static_cast<double>(hsizeValue);
    pixel_size = pixelSize;
    half_width = halfWidth;
    half_height = halfHeight;
}

Camera camera(int hsizeValue, int vsizeValue, double fieldOfViewValue) {
    return Camera(hsizeValue, vsizeValue, fieldOfViewValue);
}

Camera camera(int hsizeValue, int vsizeValue, double fieldOfViewValue, Matrix transformValue) {
    Camera resultValue = Camera(hsizeValue, vsizeValue, fieldOfViewValue);
    resultValue.transform = transformValue;
    return resultValue;
}