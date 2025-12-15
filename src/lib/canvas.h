#pragma once

#include <string>
#include <vector>

#include "color.h"

namespace rtc {

class Canvas {
public:
    Canvas(int width, int height);

    int width() const { return width_; }
    int height() const { return height_; }

    void write_pixel(int x, int y, const Color& color);
    Color pixel_at(int x, int y) const;

    std::string to_ppm() const;

private:
    int width_{0};
    int height_{0};
    std::vector<Color> pixels_;
};

}  // namespace rtc

