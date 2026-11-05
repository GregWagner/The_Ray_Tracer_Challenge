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