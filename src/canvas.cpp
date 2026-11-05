#include "canvas.hpp"

#include <cmath>
#include <string>

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

Tuple pixel_at(Canvas canvasValue, int xValue, int yValue) {
    return pixelAt(canvasValue, xValue, yValue);
}

void writePixel(Canvas &canvasValue, int xValue, int yValue, Tuple colorValue) {
    canvasValue.writePixel(xValue, yValue, colorValue);
}

void writePixel(Canvas *canvasValue, int xValue, int yValue, Tuple colorValue) {
    canvasValue->writePixel(xValue, yValue, colorValue);
}

void write_pixel(Canvas &canvasValue, int xValue, int yValue, Tuple colorValue) {
    canvasValue.writePixel(xValue, yValue, colorValue);
}

void write_pixel(Canvas *canvasValue, int xValue, int yValue, Tuple colorValue) {
    canvasValue->writePixel(xValue, yValue, colorValue);
}

std::string Canvas::toPpm() {
    std::string resultValue = "P3\n";
    resultValue = resultValue + std::to_string(width) + " " + std::to_string(height) + "\n";
    resultValue = resultValue + "255\n";

    int yIndex = 0;
    while (yIndex < height) {
        std::string rowValue = "";
        int xIndex = 0;
        while (xIndex < width) {
            Tuple pixelValue = pixelAt(xIndex, yIndex);

            double redValue = pixelValue.red;
            double greenValue = pixelValue.green;
            double blueValue = pixelValue.blue;

            if (redValue < 0.0) {
                redValue = 0.0;
            }
            if (redValue > 1.0) {
                redValue = 1.0;
            }
            if (greenValue < 0.0) {
                greenValue = 0.0;
            }
            if (greenValue > 1.0) {
                greenValue = 1.0;
            }
            if (blueValue < 0.0) {
                blueValue = 0.0;
            }
            if (blueValue > 1.0) {
                blueValue = 1.0;
            }

            int redByte = static_cast<int>(std::floor(redValue * 255.0 + 0.5));
            int greenByte = static_cast<int>(std::floor(greenValue * 255.0 + 0.5));
            int blueByte = static_cast<int>(std::floor(blueValue * 255.0 + 0.5));

            if (xIndex > 0) {
                rowValue = rowValue + " ";
            }
            rowValue = rowValue + std::to_string(redByte);
            rowValue = rowValue + " " + std::to_string(greenByte);
            rowValue = rowValue + " " + std::to_string(blueByte);

            xIndex = xIndex + 1;
        }
        resultValue = resultValue + rowValue + "\n";
        yIndex = yIndex + 1;
    }

    return resultValue;
}

std::string canvasToPpm(Canvas canvasValue) {
    return canvasValue.toPpm();
}

std::string canvas_to_ppm(Canvas canvasValue) {
    return canvasToPpm(canvasValue);
}