#pragma once

namespace rtc {

struct Color {
    double r{0.0};
    double g{0.0};
    double b{0.0};

    Color() = default;
    Color(double r_, double g_, double b_) : r(r_), g(g_), b(b_) {}

    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(double scalar) const;
    Color hadamard(const Color& other) const;

    bool operator==(const Color& other) const;
};

}  // namespace rtc

