#include "ray.hpp"

Ray ray(Tuple originValue, Tuple directionValue) {
    Ray newRay;
    newRay.origin = originValue;
    newRay.direction = directionValue;
    return newRay;
}

Tuple position(Ray rayValue, double timeValue) {
    Tuple resultValue = rayValue.origin + rayValue.direction * timeValue;
    return resultValue;
}

Tuple pointAt(Ray rayValue, double timeValue) {
    return position(rayValue, timeValue);
}

Ray transform(Ray rayValue, Matrix matrixValue) {
    Ray resultValue;
    resultValue.origin = matrixValue * rayValue.origin;
    resultValue.direction = matrixValue * rayValue.direction;
    return resultValue;
}

Ray transformRay(Ray rayValue, Matrix matrixValue) {
    return transform(rayValue, matrixValue);
}