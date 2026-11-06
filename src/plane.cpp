#include "plane.hpp"

#include <cmath>

Plane::Plane() {
}

Plane plane() {
    Plane resultValue;
    return resultValue;
}

Intersections Plane::localIntersect(const Ray &rayValue) const {
    Intersections resultValue;
    if (std::fabs(rayValue.direction.y) > 0.00001) {
        double tValue = -rayValue.origin.y / rayValue.direction.y;
        resultValue.add(Intersection(tValue, this));
    }
    return resultValue;
}

Tuple Plane::localNormalAt(const Tuple &objectPointValue) const {
    (void)objectPointValue;
    return vector(0.0, 1.0, 0.0);
}

Intersections intersect(const Plane &planeValue, const Ray &rayValue) {
    return planeValue.intersect(rayValue);
}

Intersections local_intersect(const Plane &planeValue, const Ray &rayValue) {
    return planeValue.localIntersect(rayValue);
}

Tuple normal_at(const Plane &planeValue, const Tuple &pointValue) {
    return planeValue.normalAt(pointValue);
}

Tuple local_normal_at(const Plane &planeValue, const Tuple &pointValue) {
    return planeValue.localNormalAt(pointValue);
}
