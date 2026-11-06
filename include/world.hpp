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
#endif
