#include <cmath>

#include <gtest/gtest.h>

#include "tuple.hpp"

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

TEST(Tuples, ATupleWithWEqualTo0IsAVector) {
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

TEST(Tuples, SubtractingTwoPoints) {
    Tuple pointOne = point(3, 2, 1);
    Tuple pointTwo = point(5, 6, 7);

    Tuple result = pointOne - pointTwo;

    EXPECT_TRUE(result == vector(-2, -4, -6));
}

TEST(Tuples, SubtractingVectorFromPoint) {
    Tuple pointValue = point(3, 2, 1);
    Tuple vectorValue = vector(5, 6, 7);

    Tuple result = pointValue - vectorValue;

    EXPECT_TRUE(result == point(-2, -4, -6));
}

TEST(Tuples, SubtractingTwoVectors) {
    Tuple vectorOne = vector(3, 2, 1);
    Tuple vectorTwo = vector(5, 6, 7);

    Tuple result = vectorOne - vectorTwo;

    EXPECT_TRUE(result == vector(-2, -4, -6));
}

TEST(Tuples, SubtractingVectorFromZeroVector) {
    Tuple zeroValue = vector(0, 0, 0);
    Tuple vectorValue = vector(1, -2, 3);

    Tuple result = zeroValue - vectorValue;

    EXPECT_TRUE(result == vector(-1, 2, -3));
}

TEST(Tuples, NegatingATuple) {
    Tuple aValue = tuple(1, -2, 3, -4);

    Tuple result = -aValue;

    EXPECT_TRUE(result == tuple(-1, 2, -3, 4));
}

TEST(Tuples, MultiplyingTupleByScalar) {
    Tuple aValue = tuple(1, -2, 3, -4);

    Tuple result = aValue * 3.5;

    EXPECT_TRUE(result == tuple(3.5, -7, 10.5, -14));
}

TEST(Tuples, MultiplyingTupleByFraction) {
    Tuple aValue = tuple(1, -2, 3, -4);

    Tuple result = aValue * 0.5;

    EXPECT_TRUE(result == tuple(0.5, -1, 1.5, -2));
}

TEST(Tuples, DividingTupleByScalar) {
    Tuple aValue = tuple(1, -2, 3, -4);

    Tuple result = aValue / 2;

    EXPECT_TRUE(result == tuple(0.5, -1, 1.5, -2));
}

TEST(Tuples, NormalizingVector400) {
    Tuple vectorValue = vector(4, 0, 0);

    Tuple result = normalize(vectorValue);

    EXPECT_TRUE(result == vector(1, 0, 0));
}

TEST(Tuples, NormalizingVector123) {
    Tuple vectorValue = vector(1, 2, 3);

    Tuple result = normalize(vectorValue);

    EXPECT_NEAR(result.x, 0.26726, 0.00001);
    EXPECT_NEAR(result.y, 0.53452, 0.00001);
    EXPECT_NEAR(result.z, 0.80178, 0.00001);
}

TEST(Tuples, MagnitudeOfNormalizedVector) {
    Tuple vectorValue = vector(1, 2, 3);

    Tuple normalizedValue = normalize(vectorValue);

    EXPECT_NEAR(magnitude(normalizedValue), 1.0, 0.00001);
}

TEST(Tuples, DotProductOfTwoTuples) {
    Tuple vectorOne = vector(1, 2, 3);
    Tuple vectorTwo = vector(2, 3, 4);

    double resultValue = dot(vectorOne, vectorTwo);

    EXPECT_DOUBLE_EQ(resultValue, 20.0);
}

TEST(Tuples, ColorsAreRedGreenBlueTuples) {
    Tuple colorValue = color(-0.5, 0.4, 1.7);

    EXPECT_DOUBLE_EQ(colorValue.red, -0.5);
    EXPECT_DOUBLE_EQ(colorValue.green, 0.4);
    EXPECT_DOUBLE_EQ(colorValue.blue, 1.7);
}

TEST(Tuples, CrossProductOfTwoVectors) {
    Tuple vectorA = vector(1, 2, 3);
    Tuple vectorB = vector(2, 3, 4);

    Tuple resultOne = cross(vectorA, vectorB);
    Tuple resultTwo = cross(vectorB, vectorA);

    EXPECT_TRUE(resultOne == vector(-1, 2, -1));
    EXPECT_TRUE(resultTwo == vector(1, -2, 1));
}

TEST(Tuples, MagnitudeOfVector100) {
    Tuple v = vector(1, 0, 0);

    EXPECT_DOUBLE_EQ(magnitude(v), 1.0);
}

TEST(Tuples, MagnitudeOfVector010) {
    Tuple v = vector(0, 1, 0);

    EXPECT_DOUBLE_EQ(magnitude(v), 1.0);
}

TEST(Tuples, MagnitudeOfVector001) {
    Tuple v = vector(0, 0, 1);

    EXPECT_DOUBLE_EQ(magnitude(v), 1.0);
}

TEST(Tuples, MagnitudeOfVector123) {
    Tuple v = vector(1, 2, 3);

    EXPECT_DOUBLE_EQ(magnitude(v), std::sqrt(14.0));
}

TEST(Tuples, MagnitudeOfVectorNeg1Neg2Neg3) {
    Tuple v = vector(-1, -2, -3);

    EXPECT_DOUBLE_EQ(magnitude(v), std::sqrt(14.0));
}