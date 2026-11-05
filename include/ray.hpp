#ifndef RAY_HPP
#define RAY_HPP

#include "matrix.hpp"
#include "tuple.hpp"

struct Ray {
    Tuple origin;
    Tuple direction;
};

Ray ray(Tuple originValue, Tuple directionValue);

Tuple position(Ray rayValue, double timeValue);
Tuple pointAt(Ray rayValue, double timeValue);

Ray transform(Ray rayValue, Matrix matrixValue);
Ray transformRay(Ray rayValue, Matrix matrixValue);

#endif