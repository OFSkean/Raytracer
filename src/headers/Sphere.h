//
// Created by ofsk222 on 9/2/2019.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <cmath>
#include "Ray.h"

struct Sphere {
    Vector center;
    double radius;
    Sphere() {center=Vector(); radius=1;}    //unit sphere
    Sphere(Vector c, double r) {center=c; radius=r;}

    /*
     * Gets a vector normal to the sphere in respect to the vector v
     */
    Vector getNormal(Vector v) {
        return (center - v) / radius;
    }

    /* Uses the quadratic formula to calculate if a ray intersects with the sphere. The formula
     * is based on the parametric equations of a sphere and a ray.
     *
     * If it intersects, the quadratic solution is stored in t.
    */
    bool intersects(Ray &ray, double &t) {
        Vector oc = ray.origin - center;

        double disc_a = 1;    // a = dot(ray.dest, ray.dest) = 1
        double disc_b = 2*oc.dot(ray.direction);
        double disc_c = oc.dot(oc) - radius*radius;

        double discriminant = disc_b*disc_b - 4*disc_a*disc_c;
        if (discriminant < 0) {
            return false;
        }
        else {
            discriminant = sqrt(discriminant);
            double t0 = (-disc_b - discriminant)/(2*disc_a);
            double t1 = (-disc_b + discriminant)/(2*disc_a);
            t = (t0 < t1) ? t0 : t1;
            return true;
        }
    }
};
#endif //RAYTRACER_SPHERE_H
