#include "ray.hpp"

Ray ray(Tuple originValue, Tuple directionValue) {
    Ray newRay;
    newRay.origin = originValue;
    newRay.direction = directionValue;
    return newRay;
}