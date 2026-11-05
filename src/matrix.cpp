#include "matrix.hpp"

#include <cmath>

Matrix::Matrix() {
    for (int index = 0; index < 16; index++) {
        data[index] = 0.0;
    }
}

Matrix::Matrix(std::initializer_list<double> valueList) {
    int index = 0;
    for (std::initializer_list<double>::iterator value = valueList.begin(); value != valueList.end() && index < 16; value++) {
        data[index] = *value;
        index = index + 1;
    }
    while (index < 16) {
        data[index] = 0.0;
        index = index + 1;
    }
}

Matrix::Matrix(double value0, double value1, double value2, double value3,
               double value4, double value5, double value6, double value7,
               double value8, double value9, double value10, double value11,
               double value12, double value13, double value14, double value15) {
    data[0] = value0;
    data[1] = value1;
    data[2] = value2;
    data[3] = value3;
    data[4] = value4;
    data[5] = value5;
    data[6] = value6;
    data[7] = value7;
    data[8] = value8;
    data[9] = value9;
    data[10] = value10;
    data[11] = value11;
    data[12] = value12;
    data[13] = value13;
    data[14] = value14;
    data[15] = value15;
}

double Matrix::at(int rowIndex, int columnIndex) const {
    return data[rowIndex * 4 + columnIndex];
}

double Matrix::operator()(int rowIndex, int columnIndex) const {
    return data[rowIndex * 4 + columnIndex];
}

double &Matrix::operator()(int rowIndex, int columnIndex) {
    return data[rowIndex * 4 + columnIndex];
}

Matrix::RowProxy Matrix::operator[](int rowIndex) {
    RowProxy proxyValue;
    proxyValue.matrixValue = this;
    proxyValue.rowIndex = rowIndex;
    return proxyValue;
}

Matrix::RowProxy::RowProxy() {
    matrixValue = 0;
    rowIndex = 0;
}

double &Matrix::RowProxy::operator[](int columnIndex) {
    return matrixValue->data[rowIndex * 4 + columnIndex];
}

double Matrix::RowProxy::operator[](int columnIndex) const {
    return matrixValue->data[rowIndex * 4 + columnIndex];
}

Matrix matrix(std::initializer_list<double> valueList) {
    return Matrix(valueList);
}

bool operator==(const Matrix &leftValue, const Matrix &rightValue) {
    int index = 0;
    while (index < 16) {
        double differenceValue = leftValue.data[index] - rightValue.data[index];
        if (differenceValue < 0.0) {
            differenceValue = -differenceValue;
        }
        if (differenceValue > 0.00001) {
            return false;
        }
        index = index + 1;
    }
    return true;
}