#include <gtest/gtest.h>

#include "tuple.hpp"

TEST(Tuples, ATupleWithW10IsAPoint) {
    Tuple a = tuple(4.3, -4.2, 3.1, 1.0);

    EXPECT_DOUBLE_EQ(a.x, 4.3);
    EXPECT_DOUBLE_EQ(a.y, -4.2);
    EXPECT_DOUBLE_EQ(a.z, 3.1);
    EXPECT_DOUBLE_EQ(a.w, 1.0);

    EXPECT_TRUE(a.is_point());
    EXPECT_FALSE(a.is_vector());

    EXPECT_TRUE(is_point(a));
    EXPECT_FALSE(is_vector(a));

    EXPECT_EQ(a.type(), "point");
}

TEST(Tuples, ATupleWithW0IsAVector) {
    Tuple a = tuple(4.3, -4.2, 3.1, 0.0);

    EXPECT_DOUBLE_EQ(a.x, 4.3);
    EXPECT_DOUBLE_EQ(a.y, -4.2);
    EXPECT_DOUBLE_EQ(a.z, 3.1);
    EXPECT_DOUBLE_EQ(a.w, 0.0);

    EXPECT_FALSE(a.is_point());
    EXPECT_TRUE(a.is_vector());

    EXPECT_FALSE(is_point(a));
    EXPECT_TRUE(is_vector(a));

    EXPECT_EQ(a.type(), "vector");
}

TEST(Tuples, PointCreatesTuplesWithW1) {
    Tuple p = point(4, -4, 3);

    EXPECT_TRUE(p == tuple(4, -4, 3, 1));
}

TEST(Tuples, VectorCreatesTuplesWithW0) {
    Tuple v = vector(4, -4, 3);

    EXPECT_TRUE(v == tuple(4, -4, 3, 0));
}

TEST(Tuples, AddingTwoTuples) {
    Tuple a1 = tuple(3, -2, 5, 1);
    Tuple a2 = tuple(-2, 3, 1, 0);

    Tuple result = a1 + a2;

    EXPECT_TRUE(result == tuple(1, 1, 6, 1));
}