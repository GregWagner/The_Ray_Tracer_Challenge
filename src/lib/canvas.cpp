#include "canvas.h"

#include <algorithm>
#include <sstream>

namespace {

int clamp_color_component(double component) {
    component = std::clamp(component, 0.0, 1.0);
    return static_cast<int>(component * 255.0 + 0.5);
}

}  // namespace

namespace rtc {

Canvas::Canvas(int width, int height)
    : width_(width), height_(height), pixels_(static_cast<std::size_t>(width) * static_cast<std::size_t>(height)) {}

void Canvas::write_pixel(int x, int y, const Color& color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }
    pixels_[static_cast<std::size_t>(y) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(x)] = color;
}

Color Canvas::pixel_at(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return Color{};
    }
    return pixels_[static_cast<std::size_t>(y) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(x)];
}

std::string Canvas::to_ppm() const {
    std::ostringstream ss;
    ss << "P3\n" << width_ << " " << height_ << "\n255\n";
    for (int y = 0; y < height_; ++y) {
        std::string line;
        for (int x = 0; x < width_; ++x) {
            const Color& c =
                pixels_[static_cast<std::size_t>(y) * static_cast<std::size_t>(width_) + static_cast<std::size_t>(x)];
            int r = clamp_color_component(c.r);
            int g = clamp_color_component(c.g);
            int b = clamp_color_component(c.b);

            auto append_component = [&](int value) {
                std::string text = std::to_string(value);
                if (line.size() + text.size() + 1 > 70) {
                    ss << line << "\n";
                    line.clear();
                }
                if (!line.empty()) {
                    line.push_back(' ');
                }
                line += text;
            };

            append_component(r);
            append_component(g);
            append_component(b);
        }
        if (!line.empty()) {
            ss << line << "\n";
        }
    }
    return ss.str();
}

}  // namespace rtc

