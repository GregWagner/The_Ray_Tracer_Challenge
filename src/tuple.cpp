#include "tuple.hpp"

Tuple::Tuple(double xValue, double yValue, double zValue, double wValue) {
    x = xValue;
    y = yValue;
    z = zValue;
    w = wValue;
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