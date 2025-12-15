#pragma once

#include <cmath>

namespace rtc {

struct Tuple {
    double x{0.0};
    double y{0.0};
    double z{0.0};
    double w{0.0};

    Tuple() = default;
    Tuple(double x_, double y_, double z_, double w_) : x(x_), y(y_), z(z_), w(w_) {}

    static Tuple point(double x, double y, double z) { return Tuple{x, y, z, 1.0}; }
    static Tuple vector(double x, double y, double z) { return Tuple{x, y, z, 0.0}; }

    bool is_point() const { return std::fabs(w - 1.0) < 1e-9; }
    bool is_vector() const { return std::fabs(w) < 1e-9; }

    Tuple operator+(const Tuple& other) const {
        return Tuple{x + other.x, y + other.y, z + other.z, w + other.w};
    }

    Tuple operator-(const Tuple& other) const {
        return Tuple{x - other.x, y - other.y, z - other.z, w - other.w};
    }

    Tuple operator*(double scalar) const {
        return Tuple{x * scalar, y * scalar, z * scalar, w * scalar};
    }

    Tuple operator/(double scalar) const {
        return Tuple{x / scalar, y / scalar, z / scalar, w / scalar};
    }

    bool operator==(const Tuple& other) const {
        const double eps = 1e-9;
        return std::fabs(x - other.x) < eps && std::fabs(y - other.y) < eps &&
               std::fabs(z - other.z) < eps && std::fabs(w - other.w) < eps;
    }
};

inline double magnitude(const Tuple& t) {
    return std::sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

inline Tuple normalize(const Tuple& t) {
    double mag = magnitude(t);
    return Tuple{t.x / mag, t.y / mag, t.z / mag, t.w / mag};
}

inline double dot(const Tuple& a, const Tuple& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Tuple cross(const Tuple& a, const Tuple& b) {
    return Tuple::vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

}  // namespace rtc

