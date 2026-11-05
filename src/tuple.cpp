#include "tuple.hpp"

Tuple::Tuple(double x_value, double y_value, double z_value, double w_value) {
    x = x_value;
    y = y_value;
    z = z_value;
    w = w_value;
}

bool Tuple::is_point() {
    if (w == 1.0) {
        return true;
    }
    return false;
}

bool Tuple::is_vector() {
    if (w == 0.0) {
        return true;
    }
    return false;
}

std::string Tuple::type() {
    if (is_point() == true) {
        return "point";
    }
    if (is_vector() == true) {
        return "vector";
    }
    return "tuple";
}

bool Tuple::operator==(Tuple other) {
    if (x == other.x && y == other.y && z == other.z && w == other.w) {
        return true;
    }
    return false;
}

Tuple Tuple::operator+(Tuple other) {
    Tuple result(x + other.x, y + other.y, z + other.z, w + other.w);
    return result;
}

Tuple tuple(double x, double y, double z, double w) {
    Tuple new_tuple(x, y, z, w);
    return new_tuple;
}

Tuple point(double x, double y, double z) {
    Tuple new_point = tuple(x, y, z, 1);
    return new_point;
}

Tuple vector(double x, double y, double z) {
    Tuple new_vector = tuple(x, y, z, 0);
    return new_vector;
}

bool is_point(Tuple t) {
    if (t.is_point() == true) {
        return true;
    }
    return false;
}

bool is_vector(Tuple t) {
    if (t.is_vector() == true) {
        return true;
    }
    return false;
}