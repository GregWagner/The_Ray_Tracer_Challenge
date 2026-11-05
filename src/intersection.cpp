#include "intersection.hpp"

#include <cmath>

Sphere::Sphere() {
    center = point(0.0, 0.0, 0.0);
    radius = 1.0;
}

Sphere sphere() {
    Sphere resultValue;
    return resultValue;
}

Intersection::Intersection() {
    t = 0.0;
    object = 0;
}

Intersection::Intersection(double tValue, const Sphere *objectValue) {
    t = tValue;
    object = objectValue;
}

Intersection::operator double() const {
    return t;
}

Intersection intersection(double tValue, const Sphere &sphereValue) {
    Intersection resultValue(tValue, &sphereValue);
    return resultValue;
}

Intersections::Intersections() {
    count = 0;
}

void Intersections::add(const Intersection &intersectionValue) {
    intersections.push_back(intersectionValue);
    count = static_cast<int>(intersections.size());
}

Intersection &Intersections::operator[](std::size_t indexValue) {
    return intersections[indexValue];
}

const Intersection &Intersections::operator[](std::size_t indexValue) const {
    return intersections[indexValue];
}

Intersections intersections(Intersection firstValue, Intersection secondValue) {
    Intersections resultValue;
    resultValue.add(firstValue);
    resultValue.add(secondValue);
    return resultValue;
}

Intersections intersections(std::initializer_list<Intersection> values) {
    Intersections resultValue;
    for (std::initializer_list<Intersection>::iterator value = values.begin(); value != values.end(); value++) {
        resultValue.add(*value);
    }
    return resultValue;
}

Intersections intersect(const Sphere &sphereValue, const Ray &rayValue) {
    Tuple sphereToRay = rayValue.origin - sphereValue.center;

    double aValue = dot(rayValue.direction, rayValue.direction);
    double bValue = 2.0 * dot(rayValue.direction, sphereToRay);
    double cValue = dot(sphereToRay, sphereToRay) - (sphereValue.radius * sphereValue.radius);
    double discriminantValue = bValue * bValue - 4.0 * aValue * cValue;

    Intersections resultValue;
    if (discriminantValue < 0.0) {
        return resultValue;
    }

    double sqrtValue = std::sqrt(discriminantValue);
    double t1Value = (-bValue - sqrtValue) / (2.0 * aValue);
    double t2Value = (-bValue + sqrtValue) / (2.0 * aValue);

    resultValue.add(intersection(t1Value, sphereValue));
    resultValue.add(intersection(t2Value, sphereValue));

    return resultValue;
}