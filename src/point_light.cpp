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

bool operator==(const PointLight &leftValue, const PointLight &rightValue) {
    if (!(leftValue.position == rightValue.position)) {
        return false;
    }
    if (!(leftValue.intensity == rightValue.intensity)) {
        return false;
    }
    return true;
}