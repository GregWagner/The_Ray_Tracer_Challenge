#include "point_light.hpp"

PointLight point_light(Tuple positionValue, Tuple intensityValue) {
    PointLight resultValue;
    resultValue.position = positionValue;
    resultValue.intensity = intensityValue;
    return resultValue;
}

Light light(Tuple positionValue, Tuple intensityValue) {
    return point_light(positionValue, intensityValue);
}