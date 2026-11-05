#ifndef RAY_HPP
#define RAY_HPP

#include "tuple.hpp"

struct Ray {
    Tuple origin;
    Tuple direction;
};

Ray ray(Tuple originValue, Tuple directionValue);

Tuple position(Ray rayValue, double timeValue);
Tuple pointAt(Ray rayValue, double timeValue);

#endif