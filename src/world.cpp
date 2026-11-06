#include "world.hpp"

World::World() {
    hasLight = false;
}

World world() {
    World resultValue;
    return resultValue;
}

World default_world() {
    World resultValue;

    PointLight lightValue = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));
    resultValue.lights.push_back(lightValue);
    resultValue.hasLight = true;
    resultValue.light = lightValue;

    Sphere sphereOne = sphere();
    sphereOne.material.color = color(0.8, 1.0, 0.6);
    sphereOne.material.diffuse = 0.7;
    sphereOne.material.specular = 0.2;
    resultValue.objects.push_back(sphereOne);

    Sphere sphereTwo = sphere();
    set_transform(sphereTwo, scaling(0.5, 0.5, 0.5));
    sphereTwo.material.color = color(0.8, 1.0, 0.6);
    sphereTwo.material.diffuse = 0.7;
    sphereTwo.material.specular = 0.2;
    resultValue.objects.push_back(sphereTwo);

    return resultValue;
}