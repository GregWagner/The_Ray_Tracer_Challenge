#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cstddef>
#include <initializer_list>
#include <vector>

#include "ray.hpp"
#include "tuple.hpp"

struct Sphere {
    Tuple center;
    double radius;

    Sphere();
};

Sphere sphere();

struct Intersection {
    double t;
    const Sphere *object;

    Intersection();
    Intersection(double tValue, const Sphere *objectValue);

    operator double() const;
};

struct Intersections {
    std::vector<Intersection> intersections;
    int count;

    Intersections();

    void add(const Intersection &intersectionValue);
    Intersection &operator[](std::size_t indexValue);
    const Intersection &operator[](std::size_t indexValue) const;
};

Intersections intersect(const Sphere &sphereValue, const Ray &rayValue);

Intersection intersection(double tValue, const Sphere &sphereValue);

Intersections intersections(Intersection firstValue, Intersection secondValue);
Intersections intersections(std::initializer_list<Intersection> values);

#endif