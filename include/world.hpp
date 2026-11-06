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

bool is_shadowed(World worldValue, Tuple pointValue);
bool isShadowed(World worldValue, Tuple pointValue);

Tuple color_at(World worldValue, Ray rayValue);
Tuple colorAt(World worldValue, Ray rayValue);
#endif
