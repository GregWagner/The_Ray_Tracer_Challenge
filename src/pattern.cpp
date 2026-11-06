#include "pattern.hpp"

#include <cmath>

Pattern::Pattern() {
    a = color(1.0, 1.0, 1.0);
    b = color(0.0, 0.0, 0.0);
}

Pattern::Pattern(Tuple aValue, Tuple bValue) {
    a = aValue;
    b = bValue;
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