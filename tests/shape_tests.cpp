#include <gtest/gtest.h>

#include "shape.hpp"

TEST(Shape, DefaultTransform) {
    TestShape shapeValue = test_shape();
    EXPECT_TRUE(shapeValue.transform == identityMatrix());
}

TEST(Shape, AssigningTransform) {
    TestShape shapeValue = test_shape();
    shapeValue.transform = translation(2.0, 3.0, 4.0);
    EXPECT_TRUE(shapeValue.transform == translation(2.0, 3.0, 4.0));
}
