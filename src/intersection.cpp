#include "intersection.hpp"

#include <cmath>

Sphere::Sphere() {
    center = point(0.0, 0.0, 0.0);
    radius = 1.0;
    transform = identityMatrix();
    material = ::material();
}

Sphere::Sphere(Tuple centerValue, double radiusValue) {
    center = centerValue;
    radius = radiusValue;
    transform = identityMatrix();
    material = ::material();
}

Sphere sphere() {
    Sphere resultValue;
    return resultValue;
}

void set_transform(Sphere &sphereValue, Matrix transformValue) {
    sphereValue.transform = transformValue;
}

void setTransform(Sphere &sphereValue, Matrix transformValue) {
    set_transform(sphereValue, transformValue);
}

bool operator==(const Sphere &leftValue, const Sphere &rightValue) {
    if (!(leftValue.center == rightValue.center)) {
        return false;
    }
    double radiusDifference = leftValue.radius - rightValue.radius;
    if (radiusDifference < 0.0) {
        radiusDifference = -radiusDifference;
    }
    if (radiusDifference > 0.00001) {
        return false;
    }
    if (!(leftValue.transform == rightValue.transform)) {
        return false;
    }
    if (!(leftValue.material == rightValue.material)) {
        return false;
    }
    return true;
}

Tuple Sphere::normal_at(const Tuple &pointValue) const {
    return ::normal_at(*this, pointValue);
}

Tuple Sphere::normalAt(const Tuple &pointValue) const {
    return ::normal_at(*this, pointValue);
}

Tuple normal_at(const Sphere &sphereValue, const Tuple &pointValue) {
    Matrix inverseTransformValue = inverse(sphereValue.transform);
    Tuple objectPointValue = inverseTransformValue * pointValue;
    Tuple objectNormalValue = objectPointValue - point(0.0, 0.0, 0.0);
    objectNormalValue.w = 0.0;
    objectNormalValue = normalize(objectNormalValue);

    Matrix normalTransformValue = transpose(inverseTransformValue);
    Tuple worldNormalValue = normalTransformValue * objectNormalValue;
    worldNormalValue.w = 0.0;
    return normalize(worldNormalValue);
}

Tuple normalAt(const Sphere &sphereValue, const Tuple &pointValue) {
    return normal_at(sphereValue, pointValue);
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

bool operator==(const Intersection &leftValue, const Intersection &rightValue) {
    double differenceValue = leftValue.t - rightValue.t;
    if (differenceValue < 0.0) {
        differenceValue = -differenceValue;
    }
    if (differenceValue > 0.00001) {
        return false;
    }
    if (leftValue.object != rightValue.object) {
        return false;
    }
    return true;
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

Hit Intersections::hit() const {
    return ::hit(*this);
}

Hit::Hit() {
    intersection = 0;
}

Hit::Hit(Intersection *intersectionValue) {
    intersection = intersectionValue;
}

bool Hit::has_value() const {
    if (intersection != 0) {
        return true;
    }
    return false;
}

bool Hit::hasValue() const {
    return has_value();
}

Hit::operator bool() const {
    if (intersection != 0) {
        return true;
    }
    return false;
}

Intersection &Hit::value() const {
    return *intersection;
}

Intersection *Hit::operator->() const {
    return intersection;
}

Intersection &Hit::operator*() const {
    return *intersection;
}

Hit::operator Intersection *() const {
    return intersection;
}

Hit::operator const Intersection *() const {
    return intersection;
}

Hit::operator std::optional<Intersection>() const {
    if (intersection != 0) {
        return *intersection;
    }
    return std::nullopt;
}

Hit::operator Intersection() const {
    return *intersection;
}

bool Hit::operator==(const Hit &rightValue) const {
    return intersection == rightValue.intersection;
}

bool Hit::operator==(const Intersection &rightValue) const {
    if (intersection == 0) {
        return false;
    }
    return *intersection == rightValue;
}

Computation::Computation() {
    t = 0.0;
    object = 0;
    inside = false;
    over_point = ::point(0.0, 0.0, 0.0);
    overPoint = ::point(0.0, 0.0, 0.0);
    under_point = ::point(0.0, 0.0, 0.0);
    underPoint = ::point(0.0, 0.0, 0.0);
}

Computation prepare_computations(const Intersection &intersectionValue, const Ray &rayValue) {
    Computation resultValue;
    resultValue.t = intersectionValue.t;
    resultValue.object = intersectionValue.object;

    resultValue.point = position(rayValue, resultValue.t);
    resultValue.eyev = rayValue.direction * -1.0;

    resultValue.normalv = normal_at(*resultValue.object, resultValue.point);
    if (dot(resultValue.normalv, rayValue.direction) > 0.0) {
        resultValue.inside = true;
        resultValue.normalv = resultValue.normalv * -1.0;
    } else {
        resultValue.inside = false;
    }

    resultValue.over_point = resultValue.point + (resultValue.normalv * 0.00001);
    resultValue.overPoint = resultValue.over_point;
    resultValue.under_point = resultValue.point - (resultValue.normalv * 0.00001);
    resultValue.underPoint = resultValue.under_point;

    return resultValue;
}

Computation prepareComputations(const Intersection &intersectionValue, const Ray &rayValue) {
    return prepare_computations(intersectionValue, rayValue);
}

Hit hit(const Intersections &intersectionsValue) {
    Intersection *bestValue = 0;
    for (std::size_t indexValue = 0; indexValue < intersectionsValue.intersections.size(); indexValue++) {
        const Intersection &candidateValue = intersectionsValue.intersections[indexValue];
        if (candidateValue.t >= 0.0) {
            if (bestValue == 0 || candidateValue.t < bestValue->t) {
                bestValue = const_cast<Intersection *>(&candidateValue);
            }
        }
    }
    return Hit(bestValue);
}

Intersections intersections(Intersection firstValue, Intersection secondValue) {
    Intersections resultValue;
    resultValue.add(firstValue);
    resultValue.add(secondValue);
    return resultValue;
}

Intersections intersections(Intersection firstValue, Intersection secondValue, Intersection thirdValue) {
    Intersections resultValue;
    resultValue.add(firstValue);
    resultValue.add(secondValue);
    resultValue.add(thirdValue);
    return resultValue;
}

Intersections intersections(Intersection firstValue, Intersection secondValue, Intersection thirdValue, Intersection fourthValue) {
    Intersections resultValue;
    resultValue.add(firstValue);
    resultValue.add(secondValue);
    resultValue.add(thirdValue);
    resultValue.add(fourthValue);
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
    Matrix inverseTransform = inverse(sphereValue.transform);
    Ray rayToUse = transform(rayValue, inverseTransform);

    Tuple sphereToRay = rayToUse.origin - sphereValue.center;

    double aValue = dot(rayToUse.direction, rayToUse.direction);
    double bValue = 2.0 * dot(rayToUse.direction, sphereToRay);
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