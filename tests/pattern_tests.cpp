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