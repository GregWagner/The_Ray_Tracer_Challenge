#include <fstream>
#include <iostream>

#include "canvas.hpp"
#include "intersection.hpp"
#include "ray.hpp"
#include "tuple.hpp"

int main() {
    int canvasWidth = 200;
    int canvasHeight = 200;
    Canvas canvasValue = canvas(canvasWidth, canvasHeight);

    Sphere sphereValue = sphere();

    int yIndex = 0;
    while (yIndex < canvasHeight) {
        int xIndex = 0;
        while (xIndex < canvasWidth) {
            double worldX = (xIndex - (canvasWidth / 2.0)) + 0.5;
            double worldY = ((canvasHeight / 2.0) - yIndex) - 0.5;

            Tuple originValue = point(0.0, 0.0, -5.0);
            Tuple directionValue = normalize(vector(worldX, worldY, canvasWidth));

            Ray rayValue = ray(originValue, directionValue);
            Intersections intersectionsValue = intersect(sphereValue, rayValue);
            Hit hitValue = hit(intersectionsValue);

            Tuple colorValue = color(0.0, 0.0, 0.0);
            if (hitValue) {
                colorValue = color(1.0, 0.0, 0.0);
            }

            canvasValue.writePixel(xIndex, yIndex, colorValue);
            xIndex = xIndex + 1;
        }
        yIndex = yIndex + 1;
    }

    std::ofstream outputFile("ray_sphere.ppm");
    outputFile << canvasToPpm(canvasValue);
    outputFile.close();

    std::cout << "Saved canvas to ray_sphere.ppm\n";

    return 0;
}