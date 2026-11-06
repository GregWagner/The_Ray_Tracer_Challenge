#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "material.hpp"
#include "point_light.hpp"
#include "tuple.hpp"

Tuple lighting(Material materialValue,
               PointLight lightValue,
               Tuple pointValue,
               Tuple eyevValue,
               Tuple normalValue,
               bool inShadowValue = false);

#endif