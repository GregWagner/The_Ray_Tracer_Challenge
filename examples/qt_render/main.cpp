#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QPixmap>

#include "canvas.hpp"
#include "intersection.hpp"
#include "lighting.hpp"
#include "material.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "tuple.hpp"
#include "world.hpp"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    int canvasWidth = 400;
    int canvasHeight = 400;
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

    QImage image(canvasWidth, canvasHeight, QImage::Format_RGB32);
    int y = 0;
    while (y < canvasHeight) {
        int x = 0;
        while (x < canvasWidth) {
            Tuple pixelValue = canvasValue.pixelAt(x, y);
            int redValue = static_cast<int>(pixelValue.red * 255.0 + 0.5);
            int greenValue = static_cast<int>(pixelValue.green * 255.0 + 0.5);
            int blueValue = static_cast<int>(pixelValue.blue * 255.0 + 0.5);
            if (redValue < 0) {
                redValue = 0;
            }
            if (redValue > 255) {
                redValue = 255;
            }
            if (greenValue < 0) {
                greenValue = 0;
            }
            if (greenValue > 255) {
                greenValue = 255;
            }
            if (blueValue < 0) {
                blueValue = 0;
            }
            if (blueValue > 255) {
                blueValue = 255;
            }
            image.setPixel(x, y, qRgb(redValue, greenValue, blueValue));
            x = x + 1;
        }
        y = y + 1;
    }

    QLabel label;
    label.setPixmap(QPixmap::fromImage(image));
    label.setWindowTitle("Ray Tracer");
    label.resize(image.size());
    label.show();

    return application.exec();
}