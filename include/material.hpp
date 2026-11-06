#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "tuple.hpp"

struct Material {
    Tuple color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;

    Material();
};

Material material();

bool operator==(const Material &leftValue, const Material &rightValue);
#endif
