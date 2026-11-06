#ifndef SHAPE_HPP
#define SHAPE_HPP

struct Intersections;

#include "material.hpp"
#include "matrix.hpp"
#include "tuple.hpp"

#include "ray.hpp"

struct Shape {
    Matrix transform;
    Material material;

    Shape();

    virtual ~Shape();

    Intersections intersect(const Ray &rayValue) const;

    Tuple normalAt(const Tuple &worldPointValue) const;

    virtual Intersections localIntersect(const Ray &rayValue) const = 0;

    virtual Tuple localNormalAt(const Tuple &objectPointValue) const = 0;
};

using ShapePtr = Shape *;

Intersections intersect(const Shape &shapeValue, const Ray &rayValue);
Tuple normal_at(const Shape &shapeValue, const Tuple &pointValue);

#endif