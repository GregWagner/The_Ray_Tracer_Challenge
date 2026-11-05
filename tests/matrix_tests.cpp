#include <gtest/gtest.h>

#include "matrix.hpp"
#include "tuple.hpp"

TEST(Matrix, ConstructingAndInspecting4x4) {
    Matrix M = {
        1.0, 2.0, 3.0, 4.0,
        5.5, 6.5, 7.5, 8.5,
        9.0, 10.0, 11.0, 12.0,
        13.5, 14.5, 15.5, 16.5
    };

    EXPECT_DOUBLE_EQ(M(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(M(0, 3), 4.0);
    EXPECT_DOUBLE_EQ(M(1, 0), 5.5);
    EXPECT_DOUBLE_EQ(M(1, 2), 7.5);
    EXPECT_DOUBLE_EQ(M(2, 2), 11.0);
    EXPECT_DOUBLE_EQ(M(3, 0), 13.5);
    EXPECT_DOUBLE_EQ(M(3, 2), 15.5);

    EXPECT_DOUBLE_EQ(M[0][0], 1.0);
    EXPECT_DOUBLE_EQ(M[1][2], 7.5);
    EXPECT_DOUBLE_EQ(M.data[3], 4.0);
    EXPECT_DOUBLE_EQ(M.at(3, 2), 15.5);
}

TEST(Matrix, A2x2MatrixIsRepresentable) {
    Matrix M = {
        -3.0, 5.0,
        1.0, -2.0
    };

    EXPECT_DOUBLE_EQ(M(0, 0), -3.0);
    EXPECT_DOUBLE_EQ(M(0, 1), 5.0);
    EXPECT_DOUBLE_EQ(M(1, 0), 1.0);
    EXPECT_DOUBLE_EQ(M(1, 1), -2.0);
}

TEST(Matrix, A3x3MatrixIsRepresentable) {
    Matrix M = {
        -3.0, 5.0, 0.0,
        1.0, -2.0, -7.0,
        0.0, 1.0, 1.0
    };

    EXPECT_DOUBLE_EQ(M(0, 0), -3.0);
    EXPECT_DOUBLE_EQ(M(1, 1), -2.0);
    EXPECT_DOUBLE_EQ(M(2, 2), 1.0);
}

TEST(Matrix, EqualMatricesAreEqual) {
    Matrix A = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };
    Matrix B = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };

    EXPECT_TRUE(A == B);
    EXPECT_FALSE(A != B);
}

TEST(Matrix, DifferentMatricesAreNotEqual) {
    Matrix A = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };
    Matrix B = {
        2, 3, 4, 5,
        6, 7, 8, 9,
        8, 7, 6, 5,
        4, 3, 2, 1
    };

    EXPECT_FALSE(A == B);
    EXPECT_TRUE(A != B);
}

TEST(Matrix, MultiplyingMatrixByIdentityMatrix) {
    Matrix A = {
        0, 1, 2, 4,
        1, 2, 4, 8,
        2, 4, 8, 16,
        4, 8, 16, 32
    };

    Matrix result = A * identityMatrix();

    EXPECT_TRUE(result == A);
}

TEST(Matrix, SubmatrixOf3x3Matrix) {
    Matrix matrixValue = {
        -3.0, 5.0, 0.0,
        1.0, -2.0, -7.0,
        0.0, 1.0, 1.0
    };

    Matrix resultValue = submatrix(matrixValue, 0, 2);

    Matrix expectedValue = {
        1.0, -2.0,
        0.0, 1.0
    };

    EXPECT_TRUE(resultValue == expectedValue);
}

TEST(Matrix, CofactorOf3x3Matrix) {
    Matrix matrixValue = {
        3.0, 5.0, 0.0,
        2.0, -1.0, -7.0,
        6.0, -1.0, 5.0
    };

    EXPECT_DOUBLE_EQ(minor(matrixValue, 0, 0), -12.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 0), -12.0);
    EXPECT_DOUBLE_EQ(minor(matrixValue, 1, 0), 25.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 1, 0), -25.0);
}

TEST(Matrix, MinorOf3x3Matrix) {
    Matrix matrixValue = {
        3.0, 5.0, 0.0,
        2.0, -1.0, -7.0,
        6.0, -1.0, 5.0
    };

    Matrix subMatrixValue = submatrix(matrixValue, 1, 0);

    EXPECT_DOUBLE_EQ(determinant(subMatrixValue), 25.0);
    EXPECT_DOUBLE_EQ(minor(matrixValue, 1, 0), 25.0);
}

TEST(Matrix, SubmatrixOf4x4Matrix) {
    Matrix matrixValue = {
        -6.0, 1.0, 1.0, 6.0,
        -8.0, 5.0, 8.0, 6.0,
        -1.0, 0.0, 8.0, 2.0,
        -7.0, 1.0, -1.0, 1.0
    };

    Matrix resultValue = submatrix(matrixValue, 2, 1);

    Matrix expectedValue = {
        -6.0, 1.0, 6.0,
        -8.0, 8.0, 6.0,
        -7.0, -1.0, 1.0
    };

    EXPECT_TRUE(resultValue == expectedValue);
}

TEST(Matrix, DeterminantOf3x3Matrix) {
    Matrix matrixValue = {
        1.0, 2.0, 6.0,
        -5.0, 8.0, -4.0,
        2.0, 6.0, 4.0
    };

    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 0), 56.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 1), 12.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 2), -46.0);
    EXPECT_DOUBLE_EQ(determinant(matrixValue), -196.0);
}

TEST(Matrix, InverseOfMatrix) {
    Matrix matrixValue = {
        -5.0, 2.0, 6.0, -8.0,
        1.0, -5.0, 1.0, 8.0,
        7.0, 7.0, -6.0, -7.0,
        1.0, -3.0, 7.0, 4.0
    };

    Matrix inverseValue = inverse(matrixValue);

    EXPECT_DOUBLE_EQ(determinant(matrixValue), 532.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 2, 3), -160.0);
    EXPECT_NEAR(inverseValue(3, 2), -160.0 / 532.0, 0.00001);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 3, 2), 105.0);
    EXPECT_NEAR(inverseValue(2, 3), 105.0 / 532.0, 0.00001);

    Matrix expectedValue = {
        0.21805, 0.45113, 0.24060, -0.04511,
        -0.80827, -1.45677, -0.44361, 0.52068,
        -0.07895, -0.22368, -0.05263, 0.19737,
        -0.52256, -0.81391, -0.30075, 0.30639
    };
    EXPECT_TRUE(inverseValue == expectedValue);
}

TEST(Matrix, InverseOfAnotherMatrix) {
    Matrix matrixValue = {
        8.0, -5.0, 9.0, 2.0,
        7.0, 5.0, 6.0, 1.0,
        -6.0, 0.0, 9.0, 6.0,
        -3.0, 0.0, -9.0, -4.0
    };

    Matrix resultValue = inverse(matrixValue);

    Matrix expectedValue = {
        -0.15385, -0.15385, -0.28205, -0.53846,
        -0.07692, 0.12308, 0.02564, 0.03077,
        0.35897, 0.35897, 0.43590, 0.92308,
        -0.69231, -0.69231, -0.76923, -1.92308
    };

    EXPECT_TRUE(resultValue == expectedValue);
}

TEST(Matrix, MultiplyingProductByInverse) {
    Matrix matrixA = {
        3.0, -9.0, 7.0, 3.0,
        3.0, -8.0, 2.0, -9.0,
        -4.0, 4.0, 4.0, 1.0,
        -6.0, 5.0, -1.0, 1.0
    };
    Matrix matrixB = {
        8.0, 2.0, 2.0, 2.0,
        3.0, -1.0, 7.0, 0.0,
        7.0, 0.0, 5.0, 4.0,
        6.0, -2.0, 0.0, 5.0
    };

    Matrix matrixC = matrixA * matrixB;
    Matrix resultValue = matrixC * inverse(matrixB);

    EXPECT_TRUE(resultValue == matrixA);
}

TEST(Matrix, InverseOfThirdMatrix) {
    Matrix matrixValue = {
        9.0, 3.0, 0.0, 9.0,
        -5.0, -2.0, -6.0, -3.0,
        -4.0, 9.0, 6.0, 4.0,
        -7.0, 6.0, 6.0, 2.0
    };

    Matrix resultValue = inverse(matrixValue);

    Matrix expectedValue = {
        -0.04074, -0.07778, 0.14444, -0.22222,
        -0.07778, 0.03333, 0.36667, -0.33333,
        -0.02901, -0.14630, -0.10926, 0.12963,
        0.17778, 0.06667, -0.26667, 0.33333
    };

    EXPECT_TRUE(resultValue == expectedValue);
}

TEST(Matrix, InvertibleMatrix) {
    Matrix matrixValue = {
        6.0, 4.0, 4.0, 4.0,
        5.0, 5.0, 7.0, 6.0,
        4.0, -9.0, 3.0, -7.0,
        9.0, 1.0, 7.0, -6.0
    };

    EXPECT_DOUBLE_EQ(determinant(matrixValue), -2120.0);
    EXPECT_TRUE(isInvertible(matrixValue));
}

TEST(Matrix, NoninvertibleMatrix) {
    Matrix matrixValue = {
        -4.0, 2.0, -2.0, -3.0,
        9.0, 6.0, 2.0, 6.0,
        0.0, -5.0, 1.0, -5.0,
        0.0, 0.0, 0.0, 0.0
    };

    EXPECT_DOUBLE_EQ(determinant(matrixValue), 0.0);
    EXPECT_FALSE(isInvertible(matrixValue));
}

TEST(Matrix, DeterminantOf4x4Matrix) {
    Matrix matrixValue = {
        -2.0, -8.0, 3.0, 5.0,
        -3.0, 1.0, 7.0, 3.0,
        1.0, 2.0, -9.0, 6.0,
        -6.0, 7.0, 7.0, -9.0
    };

    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 0), 690.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 1), 447.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 2), 210.0);
    EXPECT_DOUBLE_EQ(cofactor(matrixValue, 0, 3), 51.0);
    EXPECT_DOUBLE_EQ(determinant(matrixValue), -4071.0);
}

TEST(Matrix, DeterminantOf2x2Matrix) {
    Matrix matrixValue = {
        1.0, 5.0,
        -3.0, 2.0
    };

    double resultValue = determinant(matrixValue);

    EXPECT_DOUBLE_EQ(resultValue, 17.0);
}

TEST(Matrix, TransposingIdentityMatrix) {
    Matrix resultValue = transpose(identityMatrix());

    EXPECT_TRUE(resultValue == identityMatrix());
}

TEST(Matrix, TransposingAMatrix) {
    Matrix matrixValue = {
        0, 9, 3, 0,
        9, 8, 0, 8,
        1, 8, 5, 3,
        0, 0, 5, 8
    };

    Matrix resultValue = transpose(matrixValue);

    Matrix expectedValue = {
        0, 9, 1, 0,
        9, 8, 8, 0,
        3, 0, 5, 5,
        0, 8, 3, 8
    };

    EXPECT_TRUE(resultValue == expectedValue);
}

TEST(Matrix, MultiplyingByInverseTranslationMatrix) {
    Matrix transformValue = translation(5.0, -3.0, 2.0);
    Matrix inverseValue = inverse(transformValue);
    Tuple pointValue = point(-3.0, 4.0, 5.0);

    Tuple resultValue = inverseValue * pointValue;

    EXPECT_TRUE(resultValue == point(-8.0, 7.0, 3.0));
}

TEST(Matrix, TranslationDoesNotAffectVectors) {
    Matrix transformValue = translation(5.0, -3.0, 2.0);
    Tuple vectorValue = vector(-3.0, 4.0, 5.0);

    Tuple resultValue = transformValue * vectorValue;

    EXPECT_TRUE(resultValue == vectorValue);
}

TEST(Matrix, MultiplyingByTranslationMatrix) {
    Matrix transformValue = translation(5.0, -3.0, 2.0);
    Tuple pointValue = point(-3.0, 4.0, 5.0);

    Tuple resultValue = transformValue * pointValue;

    EXPECT_TRUE(resultValue == point(2.0, 1.0, 7.0));
}

TEST(Matrix, MultiplyingIdentityMatrixByTuple) {
    Tuple tupleValue = tuple(1, 2, 3, 4);

    Tuple result = identityMatrix() * tupleValue;

    EXPECT_TRUE(result == tupleValue);
}

TEST(Matrix, MultiplyingMatrixByTuple) {
    Matrix matrixValue = {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1
    };
    Tuple tupleValue = tuple(1, 2, 3, 1);

    Tuple resultValue = matrixValue * tupleValue;

    EXPECT_TRUE(resultValue == tuple(18, 24, 33, 1));
}

TEST(Matrix, MultiplyingTwoMatrices) {
    Matrix A = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };
    Matrix B = {
        -2, 1, 2, 3,
        3, 2, 1, -1,
        4, 3, 6, 5,
        1, 2, 7, 8
    };

    Matrix result = A * B;

    Matrix expected = {
        20, 22, 50, 48,
        44, 54, 114, 108,
        40, 58, 110, 102,
        16, 26, 46, 42
    };

    EXPECT_TRUE(result == expected);
}