#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "matrix.hpp"
#include "tuple.hpp"

struct Pattern {
    Tuple a;
    Tuple b;
    bool hasPattern;
    Matrix transform;

    Pattern();
    Pattern(Tuple aValue, Tuple bValue);
};

Pattern stripe_pattern(Tuple aValue, Tuple bValue);
Pattern stripePattern(Tuple aValue, Tuple bValue);

Tuple stripe_at(const Pattern &patternValue, const Tuple &pointValue);
Tuple stripeAt(const Pattern &patternValue, const Tuple &pointValue);

Tuple pattern_at(const Pattern &patternValue, const Tuple &pointValue);
Tuple patternAt(const Pattern &patternValue, const Tuple &pointValue);

void set_pattern_transform(Pattern &patternValue, Matrix transformValue);
void setPatternTransform(Pattern &patternValue, Matrix transformValue);

struct Shape;

Tuple stripe_at_object(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue);
Tuple stripeAtObject(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue);

Tuple pattern_at_object(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue);
Tuple patternAtObject(Pattern patternValue, const Shape &objectValue, const Tuple &pointValue);

Pattern stripe_pattern(Tuple aValue, Tuple bValue);
Pattern stripePattern(Tuple aValue, Tuple bValue);

Tuple stripe_at(const Pattern &patternValue, const Tuple &pointValue);
Tuple stripeAt(const Pattern &patternValue, const Tuple &pointValue);

Tuple pattern_at(const Pattern &patternValue, const Tuple &pointValue);
Tuple patternAt(const Pattern &patternValue, const Tuple &pointValue);
#endif
