#include "world.hpp"

#include "lighting.hpp"

#include <cmath>

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
    resultValue.objects.push_back(sphereTwo);

    return resultValue;
}
Intersections intersect_world(World worldValue, Ray rayValue) {
    Intersections resultValue;
    int objectIndex = 0;
    while (objectIndex < (int)worldValue.objects.size()) {
        Intersections objectIntersections = intersect(worldValue.objects[static_cast<std::size_t>(objectIndex)], rayValue);
        int intersectionIndex = 0;
        while (intersectionIndex < objectIntersections.count) {
            resultValue.add(objectIntersections[static_cast<std::size_t>(intersectionIndex)]);
            intersectionIndex = intersectionIndex + 1;
        }
        objectIndex = objectIndex + 1;
    }

    int outerIndex = 0;
    while (outerIndex < resultValue.count) {
        int innerIndex = 0;
        while (innerIndex < resultValue.count - 1) {
            if (resultValue[static_cast<std::size_t>(innerIndex)].t > resultValue[static_cast<std::size_t>(innerIndex + 1)].t) {
                Intersection temporaryValue = resultValue[static_cast<std::size_t>(innerIndex)];
                resultValue[static_cast<std::size_t>(innerIndex)] = resultValue[static_cast<std::size_t>(innerIndex + 1)];
                resultValue[static_cast<std::size_t>(innerIndex + 1)] = temporaryValue;
            }
            innerIndex = innerIndex + 1;
        }
        outerIndex = outerIndex + 1;
    }

    return resultValue;
}

Intersections intersectWorld(World worldValue, Ray rayValue) {
    return intersect_world(worldValue, rayValue);
}

Tuple shade_hit(World worldValue, Computation compsValue) {
    PointLight lightValue;
    if (worldValue.hasLight) {
        lightValue = worldValue.light;
    } else if (worldValue.lights.size() > 0) {
        lightValue = worldValue.lights[0];
    } else {
        return compsValue.object->material.color;
    }

    Tuple resultValue = lighting(compsValue.object->material, lightValue, compsValue.point, compsValue.eyev, compsValue.normalv, false);
    return resultValue;
}

Tuple shadeHit(World worldValue, Computation compsValue) {
    return shade_hit(worldValue, compsValue);
}

Tuple color_at(World worldValue, Ray rayValue) {
    Intersections intersectionsValue = intersect_world(worldValue, rayValue);
    Hit hitValue = hit(intersectionsValue);
    if (!hitValue) {
        return color(0.0, 0.0, 0.0);
    }
    Computation compsValue = prepare_computations(hitValue.value(), rayValue);
    return shade_hit(worldValue, compsValue);
}

Tuple colorAt(World worldValue, Ray rayValue) {
    return color_at(worldValue, rayValue);
}

bool is_shadowed(World worldValue, Tuple pointValue) {
    PointLight lightValue;
    if (worldValue.hasLight) {
        lightValue = worldValue.light;
    } else if (worldValue.lights.size() > 0) {
        lightValue = worldValue.lights[0];
    } else {
        return false;
    }

    Tuple vectorValue = lightValue.position - pointValue;
    double distanceValue = magnitude(vectorValue);
    Ray rayValue = ray(pointValue, normalize(vectorValue));

    Intersections intersectionsValue = intersect_world(worldValue, rayValue);
    Hit hitValue = hit(intersectionsValue);

    if (hitValue) {
        if (hitValue->t < distanceValue && hitValue->t >= 0.0) {
            return true;
        }
    }
    return false;
}

bool isShadowed(World worldValue, Tuple pointValue) {
    return is_shadowed(worldValue, pointValue);
}
