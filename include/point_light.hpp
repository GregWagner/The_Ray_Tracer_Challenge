#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "tuple.hpp"

struct PointLight {
    Tuple position;
    Tuple intensity;
};

using Light = PointLight;

PointLight point_light(Tuple positionValue, Tuple intensityValue);

Light light(Tuple positionValue, Tuple intensityValue);

bool operator==(const PointLight &leftValue, const PointLight &rightValue);

#endif