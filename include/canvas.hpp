#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <cstddef>
#include <string>
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

    std::string toPpm();
};

Canvas canvas(int widthValue, int heightValue);

Tuple pixelAt(Canvas canvasValue, int xValue, int yValue);

Tuple pixel_at(Canvas canvasValue, int xValue, int yValue);

void writePixel(Canvas &canvasValue, int xValue, int yValue, Tuple colorValue);

void writePixel(Canvas *canvasValue, int xValue, int yValue, Tuple colorValue);

void write_pixel(Canvas &canvasValue, int xValue, int yValue, Tuple colorValue);

void write_pixel(Canvas *canvasValue, int xValue, int yValue, Tuple colorValue);

std::string canvasToPpm(Canvas canvasValue);

std::string canvas_to_ppm(Canvas canvasValue);

#endif