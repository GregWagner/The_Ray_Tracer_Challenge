#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <cstddef>
#include <vector>

#include "tuple.hpp"

struct Canvas {
    int width;
    int height;
    std::vector<Tuple> pixels;

    Canvas();
    Canvas(int widthValue, int heightValue);

    Tuple pixelAt(int xValue, int yValue);
    void writePixel(int xValue, int yValue, Tuple colorValue);
};

Canvas canvas(int widthValue, int heightValue);

Tuple pixelAt(Canvas canvasValue, int xValue, int yValue);

void writePixel(Canvas *canvasValue, int xValue, int yValue, Tuple colorValue);

#endif