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