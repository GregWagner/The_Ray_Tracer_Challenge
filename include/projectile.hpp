#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "tuple.hpp"

struct Projectile {
    Tuple position;
    Tuple velocity;
};

struct Environment {
    Tuple gravity;
    Tuple wind;
};

Projectile projectile(Tuple positionValue, Tuple velocityValue);
Environment environment(Tuple gravityValue, Tuple windValue);

Projectile tick(Environment environmentValue, Projectile projectileValue);

#endif