#include <fstream>
#include <iostream>

#include "canvas.hpp"
#include "matrix.hpp"
#include "tuple.hpp"

int main() {
    int canvasWidth = 800;
    int canvasHeight = 800;
    Canvas canvasValue = canvas(canvasWidth, canvasHeight);

    Tuple centerValue = color(0.0, 0.0, 0.0);
    (void)centerValue;

    int centerX = canvasWidth / 2;
    int centerY = canvasHeight / 2;
    double radiusValue = 350.0;
    Tuple hourColor = color(1.0, 1.0, 1.0);

    int hourIndex = 0;
    while (hourIndex < 12) {
        double angleValue = (static_cast<double>(hourIndex) * PI) / 6.0;
        Matrix rotationValue = rotation_z(angleValue);
        Tuple positionValue = rotationValue * point(0.0, radiusValue, 0.0);

        int pixelX = centerX + static_cast<int>(positionValue.x);
        int pixelY = centerY - static_cast<int>(positionValue.y);

        for (int offsetY = -3; offsetY <= 3; offsetY = offsetY + 1) {
            for (int offsetX = -3; offsetX <= 3; offsetX = offsetX + 1) {
                int drawX = pixelX + offsetX;
                int drawY = pixelY + offsetY;
                if (drawX >= 0 && drawX < canvasWidth && drawY >= 0 && drawY < canvasHeight) {
                    canvasValue.writePixel(drawX, drawY, hourColor);
                }
            }
        }

        hourIndex = hourIndex + 1;
    }

    std::ofstream outputFile("clock.ppm");
    outputFile << canvasToPpm(canvasValue);
    outputFile.close();

    std::cout << "Saved canvas to clock.ppm\n";

    return 0;
}