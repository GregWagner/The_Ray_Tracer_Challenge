#include <gtest/gtest.h>

#include "tuple.hpp"

// from spec page 4
TEST(Tuples, ATupleWithWEqaulTo1IsAPoint) {
    Tuple a = tuple(4.3, -4.2, 3.1, 1.0);

    EXPECT_DOUBLE_EQ(a.x, 4.3);
    EXPECT_DOUBLE_EQ(a.y, -4.2);
    EXPECT_DOUBLE_EQ(a.z, 3.1);
    EXPECT_DOUBLE_EQ(a.w, 1.0);

    EXPECT_TRUE(a.isPoint());
    EXPECT_FALSE(a.isVector());

    EXPECT_TRUE(isPoint(a));
    EXPECT_FALSE(isVector(a));

    EXPECT_EQ(a.type(), "point");
}

TEST(Tuples, ATupleWithW0IsAVector) {
    Tuple a = tuple(4.3, -4.2, 3.1, 0.0);

    EXPECT_DOUBLE_EQ(a.x, 4.3);
    EXPECT_DOUBLE_EQ(a.y, -4.2);
    EXPECT_DOUBLE_EQ(a.z, 3.1);
    EXPECT_DOUBLE_EQ(a.w, 0.0);

    EXPECT_FALSE(a.isPoint());
    EXPECT_TRUE(a.isVector());

    EXPECT_FALSE(isPoint(a));
    EXPECT_TRUE(isVector(a));

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