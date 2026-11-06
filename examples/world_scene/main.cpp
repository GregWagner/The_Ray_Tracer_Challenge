#include <QApplication>
#include <QElapsedTimer>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QVBoxLayout>

#include "camera.hpp"
#include "canvas.hpp"
#include "lighting.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "point_light.hpp"
#include "ray.hpp"
#include "tuple.hpp"
#include "world.hpp"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    World worldValue = world();

    Sphere floorSphere = sphere();
    set_transform(floorSphere, scaling(10.0, 0.01, 10.0));
    floorSphere.material = material();
    floorSphere.material.color = color(1.0, 0.9, 0.9);
    floorSphere.material.specular = 0.0;
    worldValue.objects.push_back(floorSphere);

    Sphere leftWall = sphere();
    set_transform(leftWall, translation(0.0, 0.0, 5.0) * rotation_y(-PI / 4.0) * rotation_x(PI / 2.0) * scaling(10.0, 0.01, 10.0));
    leftWall.material = floorSphere.material;
    worldValue.objects.push_back(leftWall);

    Sphere rightWall = sphere();
    set_transform(rightWall, translation(0.0, 0.0, 5.0) * rotation_y(PI / 4.0) * rotation_x(PI / 2.0) * scaling(10.0, 0.01, 10.0));
    rightWall.material = floorSphere.material;
    worldValue.objects.push_back(rightWall);

    Sphere middleSphere = sphere();
    set_transform(middleSphere, translation(-0.5, 1.0, 0.5));
    middleSphere.material = material();
    middleSphere.material.color = color(0.1, 1.0, 0.5);
    middleSphere.material.diffuse = 0.7;
    middleSphere.material.specular = 0.3;
    worldValue.objects.push_back(middleSphere);

    Sphere rightSphere = sphere();
    set_transform(rightSphere, translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    rightSphere.material = material();
    rightSphere.material.color = color(0.5, 1.0, 0.1);
    rightSphere.material.diffuse = 0.7;
    rightSphere.material.specular = 0.3;
    worldValue.objects.push_back(rightSphere);

    Sphere leftSphere = sphere();
    set_transform(leftSphere, translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    leftSphere.material = material();
    leftSphere.material.color = color(1.0, 0.8, 0.1);
    leftSphere.material.diffuse = 0.7;
    leftSphere.material.specular = 0.3;
    worldValue.objects.push_back(leftSphere);
    worldValue.light = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));
    worldValue.hasLight = true;
    worldValue.lights.clear();
    worldValue.lights.push_back(worldValue.light);

    Camera cameraValue = camera(1280, 1024, PI / 3.0);
    cameraValue.transform = view_transform(point(0.0, 1.5, -5.0), point(0.0, 1.0, 0.0), vector(0.0, 1.0, 0.0));

    QImage image(cameraValue.hsize, cameraValue.vsize, QImage::Format_RGB32);
    image.fill(Qt::black);

    QWidget window;
    QVBoxLayout layout(&window);
    QLabel imageLabel;
    QLabel timerLabel;

    imageLabel.setPixmap(QPixmap::fromImage(image));
    timerLabel.setText("Elapsed: 0 ms");

    layout.addWidget(&imageLabel);
    layout.addWidget(&timerLabel);

    window.setWindowTitle("World Scene");
    window.show();
    application.processEvents();

    QElapsedTimer timer;
    timer.start();

    int yIndex = 0;
    while (yIndex < cameraValue.vsize) {
        int xIndex = 0;
        while (xIndex < cameraValue.hsize) {
            Ray rayValue = ray_for_pixel(cameraValue, xIndex, yIndex);
            Tuple colorValue = color_at(worldValue, rayValue);

            int redValue = static_cast<int>(colorValue.red * 255.0 + 0.5);
            int greenValue = static_cast<int>(colorValue.green * 255.0 + 0.5);
            int blueValue = static_cast<int>(colorValue.blue * 255.0 + 0.5);
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

            image.setPixel(xIndex, yIndex, qRgb(redValue, greenValue, blueValue));
            xIndex = xIndex + 1;
        }

        imageLabel.setPixmap(QPixmap::fromImage(image));
        timerLabel.setText(QString("Elapsed: %1 ms").arg(timer.elapsed()));
        application.processEvents();
        yIndex = yIndex + 1;
    }

    timerLabel.setText(QString("Finished in %1 ms").arg(timer.elapsed()));
    application.processEvents();

    return application.exec();
}