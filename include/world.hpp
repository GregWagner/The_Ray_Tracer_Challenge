#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "intersection.hpp"
#include "plane.hpp"
#include "point_light.hpp"

struct World {
    std::vector<Sphere> objects;
    std::vector<Plane> planes;
    std::vector<PointLight> lights;
    bool hasLight;
    PointLight light;

    World();
};

World world();
World default_world();

Intersections intersect_world(const World &worldValue, const Ray &rayValue);
Intersections intersectWorld(const World &worldValue, const Ray &rayValue);

#include "lighting.hpp"

Tuple shade_hit(const World &worldValue, const Computation &compsValue);
Tuple shadeHit(const World &worldValue, const Computation &compsValue);

bool is_shadowed(const World &worldValue, const Tuple &pointValue);
bool isShadowed(const World &worldValue, const Tuple &pointValue);

Tuple color_at(const World &worldValue, const Ray &rayValue);
Tuple colorAt(const World &worldValue, const Ray &rayValue);
#endif
