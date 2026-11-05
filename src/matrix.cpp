#include "matrix.hpp"

#include <cmath>

namespace {
int matrixSideFromSize(int sizeValue) {
    if (sizeValue == 1) {
        return 1;
    }
    if (sizeValue == 4) {
        return 2;
    }
    if (sizeValue == 9) {
        return 3;
    }
    if (sizeValue == 16) {
        return 4;
    }
    return 0;
}
} // namespace

Matrix::Matrix() {
    rows = 4;
    columns = 4;
    for (int index = 0; index < 16; index++) {
        data[index] = 0.0;
    }
}

Matrix::Matrix(std::initializer_list<double> valueList) {
    int sizeValue = static_cast<int>(valueList.size());
    int sideValue = matrixSideFromSize(sizeValue);

    if (sideValue == 0) {
        rows = 1;
        columns = sizeValue;
        if (columns == 0) {
            columns = 1;
        }
    } else {
        rows = sideValue;
        columns = sideValue;
    }

    int index = 0;
    for (std::initializer_list<double>::iterator value = valueList.begin(); value != valueList.end(); value++) {
        if (index >= rows * columns) {
            break;
        }
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
    rows = 4;
    columns = 4;
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
    return data[rowIndex * columns + columnIndex];
}

double Matrix::operator()(int rowIndex, int columnIndex) const {
    return data[rowIndex * columns + columnIndex];
}

double &Matrix::operator()(int rowIndex, int columnIndex) {
    return data[rowIndex * columns + columnIndex];
}

Matrix Matrix::operator*(const Matrix &otherValue) const {
    Matrix resultValue;
    for (int rowIndex = 0; rowIndex < 4; rowIndex++) {
        for (int columnIndex = 0; columnIndex < 4; columnIndex++) {
            double sumValue = 0.0;
            for (int kIndex = 0; kIndex < 4; kIndex++) {
                sumValue = sumValue + data[rowIndex * 4 + kIndex] * otherValue.data[kIndex * 4 + columnIndex];
            }
            resultValue.data[rowIndex * 4 + columnIndex] = sumValue;
        }
    }
    return resultValue;
}

Tuple Matrix::operator*(const Tuple &otherValue) const {
    double xValue = data[0] * otherValue.x + data[1] * otherValue.y + data[2] * otherValue.z + data[3] * otherValue.w;
    double yValue = data[4] * otherValue.x + data[5] * otherValue.y + data[6] * otherValue.z + data[7] * otherValue.w;
    double zValue = data[8] * otherValue.x + data[9] * otherValue.y + data[10] * otherValue.z + data[11] * otherValue.w;
    double wValue = data[12] * otherValue.x + data[13] * otherValue.y + data[14] * otherValue.z + data[15] * otherValue.w;
    return tuple(xValue, yValue, zValue, wValue);
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
    return matrixValue->data[rowIndex * matrixValue->columns + columnIndex];
}

double Matrix::RowProxy::operator[](int columnIndex) const {
    return matrixValue->data[rowIndex * matrixValue->columns + columnIndex];
}

Matrix matrix(std::initializer_list<double> valueList) {
    return Matrix(valueList);
}

Matrix identityMatrix() {
    Matrix resultValue = Matrix(1.0, 0.0, 0.0, 0.0,
                                0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, 1.0, 0.0,
                                0.0, 0.0, 0.0, 1.0);
    return resultValue;
}

Matrix identity_matrix() {
    return identityMatrix();
}

Matrix identity() {
    return identityMatrix();
}

Matrix Matrix::transpose() const {
    Matrix resultValue;
    resultValue.rows = columns;
    resultValue.columns = rows;
    for (int index = 0; index < 16; index++) {
        resultValue.data[index] = 0.0;
    }
    for (int rowIndex = 0; rowIndex < rows; rowIndex++) {
        for (int columnIndex = 0; columnIndex < columns; columnIndex++) {
            resultValue.data[columnIndex * resultValue.columns + rowIndex] = data[rowIndex * columns + columnIndex];
        }
    }
    return resultValue;
}

Matrix transpose(const Matrix &matrixValue) {
    return matrixValue.transpose();
}

Matrix transposeMatrix(const Matrix &matrixValue) {
    return transpose(matrixValue);
}

Matrix Matrix::submatrix(int removeRowValue, int removeColumnValue) const {
    return ::submatrix(*this, removeRowValue, removeColumnValue);
}

double Matrix::determinant() const {
    return ::determinant(*this);
}

Matrix submatrix(const Matrix &matrixValue, int removeRowValue, int removeColumnValue) {
    Matrix resultValue;
    resultValue.rows = matrixValue.rows - 1;
    resultValue.columns = matrixValue.columns - 1;
    for (int index = 0; index < 16; index++) {
        resultValue.data[index] = 0.0;
    }

    int destinationIndex = 0;
    for (int rowIndex = 0; rowIndex < matrixValue.rows; rowIndex++) {
        if (rowIndex == removeRowValue) {
            continue;
        }
        for (int columnIndex = 0; columnIndex < matrixValue.columns; columnIndex++) {
            if (columnIndex == removeColumnValue) {
                continue;
            }
            resultValue.data[destinationIndex] = matrixValue.data[rowIndex * matrixValue.columns + columnIndex];
            destinationIndex = destinationIndex + 1;
        }
    }

    return resultValue;
}

double determinant(const Matrix &matrixValue) {
    if (matrixValue.rows == 1) {
        return matrixValue.data[0];
    }

    if (matrixValue.rows == 2) {
        return matrixValue.data[0] * matrixValue.data[3] - matrixValue.data[1] * matrixValue.data[2];
    }

    double resultValue = 0.0;
    for (int rowIndex = 0; rowIndex < matrixValue.rows; rowIndex++) {
        Matrix subMatrixValue = submatrix(matrixValue, rowIndex, 0);
        double minorValue = determinant(subMatrixValue);
        double signValue = 1.0;
        if (rowIndex % 2 == 1) {
            signValue = -1.0;
        }
        resultValue = resultValue + matrixValue.data[rowIndex * matrixValue.columns] * signValue * minorValue;
    }
    return resultValue;
}

bool operator!=(const Matrix &leftValue, const Matrix &rightValue) {
    return !(leftValue == rightValue);
}

bool operator==(const Matrix &leftValue, const Matrix &rightValue) {
    if (leftValue.rows != rightValue.rows) {
        return false;
    }
    if (leftValue.columns != rightValue.columns) {
        return false;
    }
    int totalValue = leftValue.rows * leftValue.columns;
    int index = 0;
    while (index < totalValue) {
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