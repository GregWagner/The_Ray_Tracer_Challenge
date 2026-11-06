#include <gtest/gtest.h>

#include <cmath>

#include "intersection.hpp"
#include "matrix.hpp"
#include "pattern.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "tuple.hpp"

TEST(Pattern, CreatingStripePattern) {
    Tuple whiteValue = color(1.0, 1.0, 1.0);
    Tuple blackValue = color(0.0, 0.0, 0.0);

    Pattern patternValue = stripe_pattern(whiteValue, blackValue);

    EXPECT_TRUE(patternValue.a == whiteValue);
    EXPECT_TRUE(patternValue.b == blackValue);
}

TEST(Pattern, StripePatternConstantInY) {
    Pattern patternValue = stripe_pattern(color(1.0, 1.0, 1.0), color(0.0, 0.0, 0.0));

    EXPECT_TRUE(stripe_at(patternValue, point(0.0, 0.0, 0.0)) == color(1.0, 1.0, 1.0));
    EXPECT_TRUE(stripe_at(patternValue, point(0.0, 1.0, 0.0)) == color(1.0, 1.0, 1.0));
    EXPECT_TRUE(stripe_at(patternValue, point(0.0, 2.0, 0.0)) == color(1.0, 1.0, 1.0));
}

TEST(Pattern, StripePatternConstantInZ) {
    Pattern patternValue = stripe_pattern(color(1.0, 1.0, 1.0), color(0.0, 0.0, 0.0));

    EXPECT_TRUE(stripe_at(patternValue, point(0.0, 0.0, 0.0)) == color(1.0, 1.0, 1.0));
    EXPECT_TRUE(stripe_at(patternValue, point(0.0, 0.0, 1.0)) == color(1.0, 1.0, 1.0));
    EXPECT_TRUE(stripe_at(patternValue, point(0.0, 0.0, 2.0)) == color(1.0, 1.0, 1.0));
}

TEST(Pattern, StripePatternAlternatesInX) {
    Pattern patternValue = stripe_pattern(color(1.0, 1.0, 1.0), color(0.0, 0.0, 0.0));

    EXPECT_TRUE(stripe_at(patternValue, point(0.0, 0.0, 0.0)) == color(1.0, 1.0, 1.0));
    EXPECT_TRUE(stripe_at(patternValue, point(0.9, 0.0, 0.0)) == color(1.0, 1.0, 1.0));
    EXPECT_TRUE(stripe_at(patternValue, point(1.0, 0.0, 0.0)) == color(0.0, 0.0, 0.0));
    EXPECT_TRUE(stripe_at(patternValue, point(-0.1, 0.0, 0.0)) == color(0.0, 0.0, 0.0));
    EXPECT_TRUE(stripe_at(patternValue, point(-1.0, 0.0, 0.0)) == color(0.0, 0.0, 0.0));
    EXPECT_TRUE(stripe_at(patternValue, point(-1.1, 0.0, 0.0)) == color(1.0, 1.0, 1.0));
}

TEST(Pattern, StripesWithObjectTransformation) {
    Sphere objectValue = sphere();
    set_transform(objectValue, scaling(2.0, 2.0, 2.0));
    Pattern patternValue = stripe_pattern(color(1.0, 1.0, 1.0), color(0.0, 0.0, 0.0));

    Tuple resultValue = stripe_at_object(patternValue, objectValue, point(1.5, 0.0, 0.0));

    EXPECT_TRUE(resultValue == color(1.0, 1.0, 1.0));
}

TEST(Pattern, StripesWithPatternTransformation) {
    Sphere objectValue = sphere();
    Pattern patternValue = stripe_pattern(color(1.0, 1.0, 1.0), color(0.0, 0.0, 0.0));
    set_pattern_transform(patternValue, scaling(2.0, 2.0, 2.0));

    Tuple resultValue = stripe_at_object(patternValue, objectValue, point(1.5, 0.0, 0.0));

    EXPECT_TRUE(resultValue == color(1.0, 1.0, 1.0));
}

TEST(Pattern, StripesWithBothTransformations) {
    Sphere objectValue = sphere();
    set_transform(objectValue, scaling(2.0, 2.0, 2.0));
    Pattern patternValue = stripe_pattern(color(1.0, 1.0, 1.0), color(0.0, 0.0, 0.0));
    set_pattern_transform(patternValue, translation(0.5, 0.0, 0.0));

    Tuple resultValue = stripe_at_object(patternValue, objectValue, point(2.5, 0.0, 0.0));

    EXPECT_TRUE(resultValue == color(1.0, 1.0, 1.0));
}