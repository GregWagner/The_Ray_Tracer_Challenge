#include <fstream>
#include <iostream>

#include "canvas.hpp"
#include "intersection.hpp"
#include "lighting.hpp"
#include "material.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "tuple.hpp"

int main() {
    int canvasWidth = 800;
    int canvasHeight = 800;
    Canvas canvasValue = canvas(canvasWidth, canvasHeight);

    Sphere sphereValue = sphere();
    sphereValue.material = material();
    sphereValue.material.color = color(1.0, 0.2, 1.0);
    set_transform(sphereValue, scaling(4.0, 4.0, 4.0));

    PointLight lightValue = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));

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
                Tuple pointValue = position(rayValue, hitValue->t);
                Tuple normalValue = normal_at(*hitValue->object, pointValue);
                Tuple eyeValue = -rayValue.direction;
                colorValue = lighting(hitValue->object->material, lightValue, pointValue, eyeValue, normalValue);
            }

            canvasValue.writePixel(xIndex, yIndex, colorValue);
            xIndex = xIndex + 1;
        }
        yIndex = yIndex + 1;
    }

    std::ofstream outputFile("ray_sphere_with_lighting.ppm");
    outputFile << canvasToPpm(canvasValue);
    outputFile.close();

    std::cout << "Saved canvas to ray_sphere_with_lighting.ppm\n";

    return 0;
}