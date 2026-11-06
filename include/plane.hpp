#ifndef PLANE_HPP
#define PLANE_HPP

#include "intersection.hpp"

struct Plane : Shape {
    Plane();

    Intersections localIntersect(const Ray &rayValue) const override;

    Tuple localNormalAt(const Tuple &objectPointValue) const override;

    Tuple local_normal_at(const Tuple &objectPointValue) const {
        return localNormalAt(objectPointValue);
    }
};

Plane plane();

Intersections intersect(const Plane &planeValue, const Ray &rayValue);
Tuple normal_at(const Plane &planeValue, const Tuple &pointValue);
Tuple local_normal_at(const Plane &planeValue, const Tuple &pointValue);
#endif
