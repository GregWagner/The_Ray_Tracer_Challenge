#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "matrix.hpp"
#include "ray.hpp"
#include "tuple.hpp"

#include <cstddef>
#include <initializer_list>
#include <optional>
#include <vector>

struct Sphere {
    Tuple center;
    double radius;
    Matrix transform;

    Sphere();
    Sphere(Tuple centerValue, double radiusValue);

    Tuple normal_at(const Tuple &pointValue) const;
    Tuple normalAt(const Tuple &pointValue) const;
};

Sphere sphere();

void set_transform(Sphere &sphereValue, Matrix transformValue);

void setTransform(Sphere &sphereValue, Matrix transformValue);

Tuple normal_at(const Sphere &sphereValue, const Tuple &pointValue);

Tuple normalAt(const Sphere &sphereValue, const Tuple &pointValue);

struct Intersection {
    double t;
    const Sphere *object;

    Intersection();
    Intersection(double tValue, const Sphere *objectValue);

    operator double() const;
};

bool operator==(const Intersection &leftValue, const Intersection &rightValue);

struct Hit {
    Intersection *intersection;

    Hit();
    Hit(Intersection *intersectionValue);

    bool has_value() const;
    bool hasValue() const;

    operator bool() const;

    Intersection &value() const;
    Intersection *operator->() const;
    Intersection &operator*() const;

    operator Intersection *() const;
    operator const Intersection *() const;
    operator std::optional<Intersection>() const;
    operator Intersection() const;

    bool operator==(const Hit &rightValue) const;
    bool operator==(const Intersection &rightValue) const;
};

struct Intersections {
    std::vector<Intersection> intersections;
    int count;

    Intersections();

    void add(const Intersection &intersectionValue);
    Intersection &operator[](std::size_t indexValue);
    const Intersection &operator[](std::size_t indexValue) const;

    Hit hit() const;
};

Intersections intersect(const Sphere &sphereValue, const Ray &rayValue);

Intersection intersection(double tValue, const Sphere &sphereValue);

Intersections intersections(Intersection firstValue, Intersection secondValue);
Intersections intersections(Intersection firstValue, Intersection secondValue, Intersection thirdValue);
Intersections intersections(Intersection firstValue, Intersection secondValue, Intersection thirdValue, Intersection fourthValue);
Intersections intersections(std::initializer_list<Intersection> values);

Hit hit(const Intersections &intersectionsValue);

#endif