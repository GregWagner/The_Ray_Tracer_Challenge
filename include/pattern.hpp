#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "tuple.hpp"

struct Pattern {
    Tuple a;
    Tuple b;
    bool hasPattern;

    Pattern();
    Pattern(Tuple aValue, Tuple bValue);
};

Pattern stripe_pattern(Tuple aValue, Tuple bValue);
Pattern stripePattern(Tuple aValue, Tuple bValue);

Tuple stripe_at(const Pattern &patternValue, const Tuple &pointValue);
Tuple stripeAt(const Pattern &patternValue, const Tuple &pointValue);

Tuple pattern_at(const Pattern &patternValue, const Tuple &pointValue);
Tuple patternAt(const Pattern &patternValue, const Tuple &pointValue);
#endif
