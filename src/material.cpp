#include "material.hpp"

Material::Material() {
    color = ::color(1.0, 1.0, 1.0);
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
    hasPattern = false;
}

Material material() {
    Material resultValue;
    return resultValue;
}

bool operator==(const Material &leftValue, const Material &rightValue) {
    if (!(leftValue.color == rightValue.color)) {
        return false;
    }
    double ambientDifference = leftValue.ambient - rightValue.ambient;
    if (ambientDifference < 0.0) {
        ambientDifference = -ambientDifference;
    }
    if (ambientDifference > 0.00001) {
        return false;
    }
    double diffuseDifference = leftValue.diffuse - rightValue.diffuse;
    if (diffuseDifference < 0.0) {
        diffuseDifference = -diffuseDifference;
    }
    if (diffuseDifference > 0.00001) {
        return false;
    }
    double specularDifference = leftValue.specular - rightValue.specular;
    if (specularDifference < 0.0) {
        specularDifference = -specularDifference;
    }
    if (specularDifference > 0.00001) {
        return false;
    }
    double shininessDifference = leftValue.shininess - rightValue.shininess;
    if (shininessDifference < 0.0) {
        shininessDifference = -shininessDifference;
    }
    if (shininessDifference > 0.00001) {
        return false;
    }
    if (leftValue.hasPattern != rightValue.hasPattern) {
        return false;
    }
    if (leftValue.hasPattern) {
        if (!(leftValue.pattern.a == rightValue.pattern.a)) {
            return false;
        }
        if (!(leftValue.pattern.b == rightValue.pattern.b)) {
            return false;
        }
    }
    return true;
}