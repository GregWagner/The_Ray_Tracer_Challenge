#include <iostream>

#include "projectile.hpp"
#include "tuple.hpp"

int main() {
    Projectile projectileValue = projectile(point(0, 1, 0), normalize(vector(1, 1, 0)));
    Environment environmentValue = environment(vector(0, -0.1, 0), vector(-0.01, 0, 0));

    int tickCount = 0;

    while (true) {
        projectileValue = tick(environmentValue, projectileValue);
        tickCount = tickCount + 1;

        std::cout << "Tick " << tickCount << ": "
                  << "x=" << projectileValue.position.x
                  << ", y=" << projectileValue.position.y
                  << ", z=" << projectileValue.position.z << std::endl;

        if (projectileValue.position.y <= 0.0) {
            break;
        }
    }

    std::cout << "Hit the ground after " << tickCount << " ticks." << std::endl;
    std::cout << "Final position: x=" << projectileValue.position.x
              << ", y=" << projectileValue.position.y
              << ", z=" << projectileValue.position.z << std::endl;

    return 0;
}