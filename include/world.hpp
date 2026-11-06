#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "intersection.hpp"
#include "point_light.hpp"

struct World {
    std::vector<Sphere> objects;
    std::vector<PointLight> lights;
    bool hasLight;
    PointLight light;

    World();
};

World world();
World default_world();

Intersections intersect_world(World worldValue, Ray rayValue);
Intersections intersectWorld(World worldValue, Ray rayValue);

#include "lighting.hpp"

Tuple shade_hit(World worldValue, Computation compsValue);
Tuple shadeHit(World worldValue, Computation compsValue);
#endif
