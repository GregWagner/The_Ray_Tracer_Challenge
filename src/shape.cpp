#include "shape.hpp"
#include "intersection.hpp"
#include <cmath>

Shape::Shape() : transform(identityMatrix()), material(::material()) {
}

Shape::~Shape() = default;

Intersections Shape::intersect(const Ray &rayValue) const {
    Matrix inverseTransform = inverse(transform);
    Ray objectRay = ::transform(rayValue, inverseTransform);
    savedRay = objectRay;
    saved_ray = objectRay;
    Intersections resultValue = localIntersect(objectRay);
    std::size_t indexValue = 0;
    while (indexValue < resultValue.intersections.size()) {
        resultValue.intersections[indexValue].object = this;
        indexValue = indexValue + 1;
    }
    return resultValue;
}

Tuple Shape::normalAt(const Tuple &worldPointValue) const {
    Matrix inverseTransform = inverse(transform);
    Tuple objectPointValue = inverseTransform * worldPointValue;
    Tuple objectNormalValue = localNormalAt(objectPointValue);
    Matrix normalTransform = transpose(inverseTransform);
    Tuple worldNormalValue = normalTransform * objectNormalValue;
    worldNormalValue.w = 0.0;
    return normalize(worldNormalValue);
}

Intersections intersect(const Shape &shapeValue, const Ray &rayValue) {
    return shapeValue.intersect(rayValue);
}

Tuple normal_at(const Shape &shapeValue, const Tuple &pointValue) {
    return shapeValue.normalAt(pointValue);
}

void set_transform(Shape &shapeValue, Matrix transformValue) {
    shapeValue.transform = transformValue;
}

void setTransform(Shape &shapeValue, Matrix transformValue) {
    set_transform(shapeValue, transformValue);
}

TestShape::TestShape() {
}

Intersections TestShape::localIntersect(const Ray &rayValue) const {
    (void)rayValue;
    Intersections resultValue;
    return resultValue;
}

Tuple TestShape::localNormalAt(const Tuple &objectPointValue) const {
    (void)objectPointValue;
    return objectPointValue;
}

TestShape test_shape() {
    TestShape resultValue;
    return resultValue;
}