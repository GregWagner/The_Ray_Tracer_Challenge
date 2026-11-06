#include "pattern.hpp"

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