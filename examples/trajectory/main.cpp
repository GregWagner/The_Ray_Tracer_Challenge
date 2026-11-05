#include <fstream>
#include <iostream>
#include <string>

#include "canvas.hpp"
#include "projectile.hpp"
#include "tuple.hpp"

int main() {
    Canvas canvasValue = canvas(1100, 400);

    Tuple velocityValue = normalize(vector(1.0, 1.8, 0.0)) * 10.0;
    Projectile projectileValue = projectile(point(0.0, 1.0, 0.0), velocityValue);
    Environment environmentValue = environment(vector(0.0, -0.1, 0.0), vector(-0.01, 0.0, 0.0));

    int tickCount = 0;

    while (projectileValue.position.y > 0.0) {
        projectileValue = tick(environmentValue, projectileValue);
        tickCount = tickCount + 1;

        int centerX = static_cast<int>(projectileValue.position.x);
        int centerY = static_cast<int>(canvasValue.height - projectileValue.position.y);

        for (int offsetY = -1; offsetY <= 1; offsetY = offsetY + 1) {
            for (int offsetX = -1; offsetX <= 1; offsetX = offsetX + 1) {
                int pixelX = centerX + offsetX;
                int pixelY = centerY + offsetY;
                if (pixelX >= 0 && pixelX < canvasValue.width && pixelY >= 0 && pixelY < canvasValue.height) {
                    canvasValue.writePixel(pixelX, pixelY, color(1.0, 0.0, 0.0));
                }
            }
        }
    }

    std::ofstream outputFile("trajectory.ppm");
    outputFile << canvasToPpm(canvasValue);
    outputFile.close();

    std::cout << "Hit the ground after " << tickCount << " ticks.\n";
    std::cout << "Saved canvas to trajectory.ppm\n";

    return 0;
}