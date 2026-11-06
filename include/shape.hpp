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
    mutable Ray savedRay;
    mutable Ray saved_ray;

    Shape();

    virtual ~Shape();

    Intersections intersect(const Ray &rayValue) const;

    Tuple normalAt(const Tuple &worldPointValue) const;

    virtual Intersections localIntersect(const Ray &rayValue) const = 0;

    virtual Tuple localNormalAt(const Tuple &objectPointValue) const = 0;

    Tuple local_normal_at(const Tuple &objectPointValue) const {
        return localNormalAt(objectPointValue);
    }
};

using ShapePtr = Shape *;

struct TestShape : Shape {
    TestShape();

    Intersections localIntersect(const Ray &rayValue) const override;
    Tuple localNormalAt(const Tuple &objectPointValue) const override;
};

TestShape test_shape();

Intersections intersect(const Shape &shapeValue, const Ray &rayValue);
Tuple normal_at(const Shape &shapeValue, const Tuple &pointValue);
Tuple local_normal_at(const Shape &shapeValue, const Tuple &pointValue);

void set_transform(Shape &shapeValue, Matrix transformValue);
void setTransform(Shape &shapeValue, Matrix transformValue);

#endif