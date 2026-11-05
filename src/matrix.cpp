#include "matrix.hpp"

#include <cmath>

Matrix::Matrix() {
    rows = 4;
    columns = 4;
    int index = 0;
    while (index < rows * columns) {
        data.push_back(0.0);
        index = index + 1;
    }
}

Matrix::Matrix(std::initializer_list<double> valueList) {
    int sizeValue = static_cast<int>(valueList.size());
    int sideValue = 0;
    if (sizeValue == 1) {
        sideValue = 1;
    } else if (sizeValue == 4) {
        sideValue = 2;
    } else if (sizeValue == 9) {
        sideValue = 3;
    } else if (sizeValue == 16) {
        sideValue = 4;
    } else {
        sideValue = 0;
    }

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
        data.push_back(*value);
        index = index + 1;
    }
    while (index < rows * columns) {
        data.push_back(0.0);
        index = index + 1;
    }
}

Matrix::Matrix(double value0, double value1, double value2, double value3,
               double value4, double value5, double value6, double value7,
               double value8, double value9, double value10, double value11,
               double value12, double value13, double value14, double value15) {
    rows = 4;
    columns = 4;
    data.push_back(value0);
    data.push_back(value1);
    data.push_back(value2);
    data.push_back(value3);
    data.push_back(value4);
    data.push_back(value5);
    data.push_back(value6);
    data.push_back(value7);
    data.push_back(value8);
    data.push_back(value9);
    data.push_back(value10);
    data.push_back(value11);
    data.push_back(value12);
    data.push_back(value13);
    data.push_back(value14);
    data.push_back(value15);
}

double Matrix::at(int rowIndex, int columnIndex) const {
    return data[static_cast<std::size_t>(rowIndex * columns + columnIndex)];
}

double Matrix::operator()(int rowIndex, int columnIndex) const {
    return data[static_cast<std::size_t>(rowIndex * columns + columnIndex)];
}

double &Matrix::operator()(int rowIndex, int columnIndex) {
    return data[static_cast<std::size_t>(rowIndex * columns + columnIndex)];
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
    return matrixValue->data[static_cast<std::size_t>(rowIndex * matrixValue->columns + columnIndex)];
}

double Matrix::RowProxy::operator[](int columnIndex) const {
    return matrixValue->data[static_cast<std::size_t>(rowIndex * matrixValue->columns + columnIndex)];
}

Matrix matrix(std::initializer_list<double> valueList) {
    return Matrix(valueList);
}

bool operator==(const Matrix &leftValue, const Matrix &rightValue) {
    if (leftValue.rows != rightValue.rows) {
        return false;
    }
    if (leftValue.columns != rightValue.columns) {
        return false;
    }
    size_t index = 0;
    while (index < leftValue.data.size()) {
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