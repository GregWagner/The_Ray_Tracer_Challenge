#include <QApplication>

#include "camera.hpp"
#include "canvas.hpp"
#include "lighting.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "point_light.hpp"
#include "qt_canvas.h"
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

    Sphere leftSphere = sphere();
    set_transform(leftSphere, translation(-1.0, 1.0, 0.0));
    leftSphere.material = material();
    leftSphere.material.color = color(1.0, 0.0, 0.0);
    leftSphere.material.diffuse = 0.7;
    leftSphere.material.specular = 0.3;
    worldValue.objects.push_back(leftSphere);

    Sphere rightSphere = sphere();
    set_transform(rightSphere, translation(1.0, 1.0, 0.0));
    rightSphere.material = material();
    rightSphere.material.color = color(0.0, 0.0, 1.0);
    rightSphere.material.diffuse = 0.7;
    rightSphere.material.specular = 0.3;
    worldValue.objects.push_back(rightSphere);

    Plane wallPlane = plane();
    set_transform(wallPlane, translation(0.0, 0.0, 5.0) * rotation_x(PI / 2.0));
    wallPlane.material = material();
    wallPlane.material.color = color(0.9, 0.9, 1.0);
    wallPlane.material.specular = 0.0;
    worldValue.planes.push_back(wallPlane);

    worldValue.light = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));
    worldValue.hasLight = true;
    worldValue.lights.clear();
    worldValue.lights.push_back(worldValue.light);

    Camera cameraValue = camera(400, 200, PI / 3.0);
    cameraValue.transform = view_transform(point(0.0, 1.5, -5.0), point(0.0, 1.0, 0.0), vector(0.0, 1.0, 0.0));

    Canvas canvasValue = render(cameraValue, worldValue);

    showCanvas(application, canvasValue, "Plane Scene");

    return 0;
}