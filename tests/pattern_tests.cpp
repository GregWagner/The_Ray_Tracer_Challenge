#include <gtest/gtest.h>

#include "pattern.hpp"
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