#include <QApplication>

#include "canvas.hpp"
#include "intersection.hpp"
#include "lighting.hpp"
#include "material.hpp"
#include "point_light.hpp"
#include "qt_canvas.h"
#include "ray.hpp"
#include "tuple.hpp"
#include "world.hpp"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    int canvasWidth = 800;
    int canvasHeight = 800;
    Canvas canvasValue = canvas(canvasWidth, canvasHeight);

    Sphere sphereValue = sphere();
    sphereValue.material = material();
    sphereValue.material.color = color(1.0, 0.2, 1.0);
    set_transform(sphereValue, scaling(4.0, 4.0, 4.0));

    World worldValue = world();
    worldValue.objects.push_back(sphereValue);
    PointLight lightValue = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));
    worldValue.lights.push_back(lightValue);
    worldValue.hasLight = true;
    worldValue.light = lightValue;

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
                Computation comps = prepare_computations(*hitValue, rayValue);
                colorValue = shade_hit(worldValue, comps);
            }

            canvasValue.writePixel(xIndex, yIndex, colorValue);
            xIndex = xIndex + 1;
        }
        yIndex = yIndex + 1;
    }

    showCanvas(application, canvasValue, "Ray Sphere With Lighting");

    return 0;
}