//
// Created by ofsk222 on 9/2/2019.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vector.h"

struct Ray {
    Vector origin;
    Vector direction;
    Ray(Vector a, Vector b) {origin=a; direction=b;}
};
#endif //RAYTRACER_RAY_H
