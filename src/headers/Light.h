//
// Created by ofsk222 on 9/2/2019.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include <cmath>
#include "Color.h"
#include "Sphere.h"

struct Light {
    Sphere sphere;
    Color color;

    Light(Sphere s, Color c) {sphere = s; color = c;}

    Color getIntensity(Vector v, Vector normal) {
        return color * (v - sphere.center).normalize().dot(normal);
    }
};
#endif //RAYTRACER_LIGHT_H
