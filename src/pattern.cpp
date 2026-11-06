#include "pattern.hpp"

#include "shape.hpp"

#include <cmath>

Pattern::Pattern() {
    a = color(1.0, 1.0, 1.0);
    b = color(0.0, 0.0, 0.0);
    hasPattern = false;
    transform = identityMatrix();
}

Pattern::Pattern(Tuple aValue, Tuple bValue) {
    a = aValue;
    b = bValue;
    hasPattern = true;
    transform = identityMatrix();
}

Pattern stripe_pattern(Tuple aValue, Tuple bValue) {
    Pattern resultValue(aValue, bValue);
    return resultValue;
}

Pattern stripePattern(Tuple aValue, Tuple bValue) {
    return stripe_pattern(aValue, bValue);
}

Tuple stripe_at(const Pattern &patternValue, const Tuple &pointValue) {
    int floorValue = static_cast<int>(std::floor(pointValue.x));
    floorValue = floorValue % 2;
    if (floorValue < 0) {
        floorValue = floorValue + 2;
    }

    if (floorValue == 0) {
        return patternValue.a;
    }
    return patternValue.b;
}

Tuple stripeAt(const Pattern &patternValue, const Tuple &pointValue) {
    return stripe_at(patternValue, pointValue);
}

Tuple pattern_at(const Pattern &patternValue, const Tuple &pointValue) {
    return stripe_at(patternValue, pointValue);
}

Tuple patternAt(const Pattern &patternValue, const Tuple &pointValue) {
    return pattern_at(patternValue, pointValue);
}

void set_pattern_transform(Pattern &patternValue, Matrix transformValue) {
    patternValue.transform = transformValue;
}

void setPatternTransform(Pattern &patternValue, Matrix transformValue) {
    set_pattern_transform(patternValue, transformValue);
}

Tuple stripe_at_object(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue) {
    Tuple objectPoint = inverse(objectValue.transform) * pointValue;
    Tuple patternPoint = inverse(patternValue.transform) * objectPoint;
    return stripe_at(patternValue, patternPoint);
}

Tuple stripeAtObject(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue) {
    return stripe_at_object(patternValue, objectValue, pointValue);
}

Tuple pattern_at_object(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue) {
    return stripe_at_object(patternValue, objectValue, pointValue);
}

Tuple patternAtObject(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue) {
    return pattern_at_object(patternValue, objectValue, pointValue);
}