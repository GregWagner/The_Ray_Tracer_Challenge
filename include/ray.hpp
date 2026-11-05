#ifndef RAY_HPP
#define RAY_HPP

#include "tuple.hpp"

struct Ray {
    Tuple origin;
    Tuple direction;
};

Ray ray(Tuple originValue, Tuple directionValue);

#endif