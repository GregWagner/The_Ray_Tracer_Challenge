// Example program from Chapter 1 using vectors and points.
#include "projectile.hpp"

Projectile projectile(Tuple positionValue, Tuple velocityValue) {
    Projectile newProjectile;
    newProjectile.position = positionValue;
    newProjectile.velocity = velocityValue;
    return newProjectile;
}

Environment environment(Tuple gravityValue, Tuple windValue) {
    Environment newEnvironment;
    newEnvironment.gravity = gravityValue;
    newEnvironment.wind = windValue;
    return newEnvironment;
}

Projectile tick(Environment environmentValue, Projectile projectileValue) {
    Tuple positionValue = projectileValue.position + projectileValue.velocity;
    Tuple velocityValue =
        projectileValue.velocity + environmentValue.gravity + environmentValue.wind;
    return projectile(positionValue, velocityValue);
}