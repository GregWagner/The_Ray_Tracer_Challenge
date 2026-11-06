#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "tuple.hpp"

struct Pattern {
    Tuple a;
    Tuple b;

    Pattern();
    Pattern(Tuple aValue, Tuple bValue);
};

Pattern stripe_pattern(Tuple aValue, Tuple bValue);
Pattern stripePattern(Tuple aValue, Tuple bValue);
#endif
