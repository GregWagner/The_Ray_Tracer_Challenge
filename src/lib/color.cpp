#include "color.h"

#include <cmath>

namespace rtc {

Color Color::operator+(const Color& other) const {
    return Color{r + other.r, g + other.g, b + other.b};
}

Color Color::operator-(const Color& other) const {
    return Color{r - other.r, g - other.g, b - other.b};
}

Color Color::operator*(double scalar) const {
    return Color{r * scalar, g * scalar, b * scalar};
}

Color Color::hadamard(const Color& other) const {
    return Color{r * other.r, g * other.g, b * other.b};
}

bool Color::operator==(const Color& other) const {
    const double eps = 1e-9;
    return std::fabs(r - other.r) < eps && std::fabs(g - other.g) < eps && std::fabs(b - other.b) < eps;
}

}  // namespace rtc

