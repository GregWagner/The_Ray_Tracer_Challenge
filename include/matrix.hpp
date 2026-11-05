#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "tuple.hpp"

#include <cstddef>
#include <initializer_list>

struct Matrix {
    int rows;
    int columns;
    double data[16];

    Matrix();
    Matrix(std::initializer_list<double> valueList);
    Matrix(double value0, double value1, double value2, double value3,
           double value4, double value5, double value6, double value7,
           double value8, double value9, double value10, double value11,
           double value12, double value13, double value14, double value15);

    double at(int rowIndex, int columnIndex) const;
    double operator()(int rowIndex, int columnIndex) const;
    double &operator()(int rowIndex, int columnIndex);

    Matrix operator*(const Matrix &otherValue) const;

    Tuple operator*(const Tuple &otherValue) const;

    struct RowProxy {
        Matrix *matrixValue;
        int rowIndex;

        RowProxy();

        double &operator[](int columnIndex);
        double operator[](int columnIndex) const;
    };
    RowProxy operator[](int rowIndex);
};

using Matrix4 = Matrix;
using Matrix4x4 = Matrix;

Matrix matrix(std::initializer_list<double> valueList);

Matrix identityMatrix();
Matrix identity_matrix();
Matrix identity();

bool operator==(const Matrix &leftValue, const Matrix &rightValue);
bool operator!=(const Matrix &leftValue, const Matrix &rightValue);

#endif