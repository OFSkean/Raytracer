//
// Created by ofsk222 on 9/2/2019.
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H

#include <cmath>

// three-dimensional vector
struct Vector {
    double x, y, z;
    Vector() {x=y=z=0;}  // default to zero vector
    Vector(double X, double Y, double Z) {x=X; y=Y; z=Z;}
    Vector operator - (Vector p) {return {x-p.x, y-p.y, z-p.z};}
    Vector operator + (Vector p) {return {x+p.x, y+p.y, z+p.z};}
    Vector operator * (double d) {return {x*d, y*d, z*d};}
    Vector operator / (double d) {return {x/d, y/d, z/d};}
    Vector normalize() {
        double magnitude = sqrt(x*x + y*y + z*z);
        return {x/magnitude, y/magnitude, z/magnitude};
    }
    double dot(Vector b) {
        return x*b.x + y*b.y + z*b.z;
    }
};
#endif //RAYTRACER_VECTOR_H
