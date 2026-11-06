#include <fstream>
#include <iostream>

#include "camera.hpp"
#include "canvas.hpp"
#include "lighting.hpp"
#include "material.hpp"
#include "matrix.hpp"
#include "point_light.hpp"
#include "tuple.hpp"
#include "world.hpp"

int main() {
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

    PointLight lightValue = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));
    worldValue.lights.push_back(lightValue);
    worldValue.hasLight = true;
    worldValue.light = lightValue;

    Camera cameraValue = camera(1280, 1024, PI / 3.0);
    cameraValue.transform = view_transform(point(0.0, 1.5, -5.0), point(0.0, 1.0, 0.0), vector(0.0, 1.0, 0.0));

    Canvas canvasValue = render(cameraValue, worldValue);

    std::ofstream outputFile("world_scene.ppm");
    outputFile << canvasToPpm(canvasValue);
    outputFile.close();

    std::cout << "Saved canvas to world_scene.ppm\n";

    return 0;
}