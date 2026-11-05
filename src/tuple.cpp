#include "tuple.hpp"

#include <cmath>

#include <cmath>

Tuple::Tuple() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 0.0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
    alpha = 0.0;
}

Tuple::Tuple(double xValue, double yValue, double zValue, double wValue) {
    x = xValue;
    y = yValue;
    z = zValue;
    w = wValue;
    red = xValue;
    green = yValue;
    blue = zValue;
    alpha = wValue;
}

bool Tuple::isPoint() {
    if (w == 1.0) {
        return true;
    }
    return false;
}

bool Tuple::isVector() {
    if (w == 0.0) {
        return true;
    }
    return false;
}

std::string Tuple::type() {
    if (isPoint() == true) {
        return "point";
    }
    if (isVector() == true) {
        return "vector";
    }
    return "tuple";
}

bool Tuple::operator==(Tuple otherValue) {
    if (x == otherValue.x && y == otherValue.y && z == otherValue.z && w == otherValue.w) {
        return true;
    }
    return false;
}

Tuple Tuple::operator+(Tuple otherValue) {
    Tuple resultValue(x + otherValue.x, y + otherValue.y, z + otherValue.z, w + otherValue.w);
    return resultValue;
}

Tuple Tuple::operator-(Tuple otherValue) {
    Tuple resultValue(x - otherValue.x, y - otherValue.y, z - otherValue.z, w - otherValue.w);
    return resultValue;
}

Tuple Tuple::operator-() {
    Tuple resultValue(-x, -y, -z, -w);
    return resultValue;
}

Tuple Tuple::operator*(double scalarValue) {
    Tuple resultValue(x * scalarValue, y * scalarValue, z * scalarValue, w * scalarValue);
    return resultValue;
}

Tuple Tuple::operator/(double scalarValue) {
    Tuple resultValue(x / scalarValue, y / scalarValue, z / scalarValue, w / scalarValue);
    return resultValue;
}

Tuple tuple(double xValue, double yValue, double zValue, double wValue) {
    Tuple newTuple(xValue, yValue, zValue, wValue);
    return newTuple;
}

Tuple point(double xValue, double yValue, double zValue) {
    Tuple newPoint = tuple(xValue, yValue, zValue, 1);
    return newPoint;
}

Tuple vector(double xValue, double yValue, double zValue) {
    Tuple newVector = tuple(xValue, yValue, zValue, 0);
    return newVector;
}

Tuple color(double redValue, double greenValue, double blueValue) {
    Tuple newColor = tuple(redValue, greenValue, blueValue, 0.0);
    return newColor;
}

bool isPoint(Tuple tupleValue) {
    if (tupleValue.isPoint() == true) {
        return true;
    }
    return false;
}

bool isVector(Tuple tupleValue) {
    if (tupleValue.isVector() == true) {
        return true;
    }
    return false;
}

double magnitude(Tuple tupleValue) {
    double value = tupleValue.x * tupleValue.x;
    value = value + tupleValue.y * tupleValue.y;
    value = value + tupleValue.z * tupleValue.z;
    return std::sqrt(value);
}

Tuple normalize(Tuple tupleValue) {
    double magValue = magnitude(tupleValue);
    Tuple resultValue(tupleValue.x / magValue, tupleValue.y / magValue, tupleValue.z / magValue, tupleValue.w);
    return resultValue;
}

double dot(Tuple tupleValueOne, Tuple tupleValueTwo) {
    double resultValue = (tupleValueOne.x * tupleValueTwo.x) + (tupleValueOne.y * tupleValueTwo.y) + (tupleValueOne.z * tupleValueTwo.z) + (tupleValueOne.w * tupleValueTwo.w);
    return resultValue;
}

Tuple cross(Tuple tupleValueOne, Tuple tupleValueTwo) {
    Tuple resultValue(
        (tupleValueOne.y * tupleValueTwo.z) - (tupleValueOne.z * tupleValueTwo.y),
        (tupleValueOne.z * tupleValueTwo.x) - (tupleValueOne.x * tupleValueTwo.z),
        (tupleValueOne.x * tupleValueTwo.y) - (tupleValueOne.y * tupleValueTwo.x),
        0.0);
    return resultValue;
}