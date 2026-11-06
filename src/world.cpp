#include "world.hpp"

World world() {
    World resultValue;
    return resultValue;
}

World default_world() {
    World resultValue;

    PointLight lightValue = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));
    resultValue.lights.push_back(lightValue);

    Sphere sphereOne = sphere();
    resultValue.objects.push_back(sphereOne);

    Sphere sphereTwo = sphere();
    set_transform(sphereTwo, scaling(0.5, 0.5, 0.5));
    resultValue.objects.push_back(sphereTwo);

    return resultValue;
}