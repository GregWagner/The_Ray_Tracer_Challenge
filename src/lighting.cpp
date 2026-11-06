#include "lighting.hpp"

#include <cmath>

Tuple lighting(Material materialValue,
               PointLight lightValue,
               Tuple pointValue,
               Tuple eyevValue,
               Tuple normalValue,
               bool inShadowValue) {
    Tuple materialColor = materialValue.color;
    if (materialValue.hasPattern || materialValue.pattern.hasPattern) {
        materialColor = pattern_at(materialValue.pattern, pointValue);
    }
    Tuple effectiveColor = materialColor * lightValue.intensity;
    Tuple lightVector = lightValue.position - pointValue;
    lightVector = normalize(lightVector);

    Tuple ambientColor = effectiveColor * materialValue.ambient;

    Tuple diffuseColor = color(0.0, 0.0, 0.0);
    Tuple specularColor = color(0.0, 0.0, 0.0);

    if (!inShadowValue) {
        double lightDotNormal = dot(normalValue, lightVector);
        if (lightDotNormal < 0.0) {
            lightDotNormal = 0.0;
        }

        diffuseColor = effectiveColor * (materialValue.diffuse * lightDotNormal);

        Tuple reflectVector = reflect(-lightVector, normalValue);
        double reflectDotEye = dot(reflectVector, eyevValue);
        if (reflectDotEye < 0.0) {
            reflectDotEye = 0.0;
        }

        double specularFactor = std::pow(reflectDotEye, materialValue.shininess);
        specularColor = lightValue.intensity * (materialValue.specular * specularFactor);
    }

    Tuple resultColor = ambientColor + diffuseColor;
    resultColor = resultColor + specularColor;

    return resultColor;
}