#include "canvas.hpp"

Canvas::Canvas() {
    width = 0;
    height = 0;
}

Canvas::Canvas(int widthValue, int heightValue) {
    width = widthValue;
    height = heightValue;
    int index = 0;
    while (index < width * height) {
        pixels.push_back(color(0.0, 0.0, 0.0));
        index = index + 1;
    }
}

Tuple Canvas::pixelAt(int xValue, int yValue) {
    int index = yValue * width + xValue;
    return pixels[static_cast<std::size_t>(index)];
}

void Canvas::writePixel(int xValue, int yValue, Tuple colorValue) {
    int index = yValue * width + xValue;
    pixels[static_cast<std::size_t>(index)] = colorValue;
}

Canvas canvas(int widthValue, int heightValue) {
    Canvas newCanvas(widthValue, heightValue);
    return newCanvas;
}

Tuple pixelAt(Canvas canvasValue, int xValue, int yValue) {
    return canvasValue.pixelAt(xValue, yValue);
}

void writePixel(Canvas &canvasValue, int xValue, int yValue, Tuple colorValue) {
    canvasValue.writePixel(xValue, yValue, colorValue);
}

Canvas writePixel(Canvas canvasValue, int xValue, int yValue, Tuple colorValue) {
    canvasValue.writePixel(xValue, yValue, colorValue);
    return canvasValue;
}