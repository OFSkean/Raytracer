#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <fstream>

struct Vector {
    double x, y, z;
    Vector() {x=y=z=0;}
    Vector(double X, double Y, double Z) {x=X; y=Y; z=Z;}
    Vector operator - (Vector p) {return {x-p.x, y-p.y, z-p.z};}
    Vector operator + (Vector p) {return {x+p.x, y+p.y, z+p.z};}
    Vector operator * (double d) {return {x*d, y*d, z*d};}
    Vector operator / (double d) {return {x/d, y/d, z/d};}
    Vector normalize() {
        double magnitude = sqrt(x*x+y*y+z*z);
        return {x/magnitude, y/magnitude, z/magnitude};
    }
};

struct Color {
    double r, b, g;
    Color() {r=b=g=0;}
    Color (double R, double B, double G) {r=R; b=B; g=G;}
    Color operator * (double d) {
        //saturate so that values don't over/underflow
        if (d > 0) {
            return { std::min(d*r, 255.0), std::min(d*b, 255.0), std::min(d*g, 255.0) };
        }
        else {
           return {};
        }
    }
};

struct Ray {
    Vector origin;
    Vector direction;
    Ray(Vector a, Vector b) {origin=a; direction=b;}
};

double dot(Vector a, Vector b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

struct Sphere {
    Vector center;
    double radius;
    Sphere() {center=Vector(); radius=1;}    //unit sphere
    Sphere(Vector c, double r) {center=c; radius=r;}

    Vector getNormal(Vector v) {
        return (center - v) / radius;
    }
    bool intersects(Ray &ray, double &t) {
        Vector oc = ray.origin - center;

        double disc_a = 1;    // a = dot(ray.dest, ray.dest) = 1
        double disc_b = 2*dot(oc, ray.direction);
        double disc_c = dot(oc, oc) - radius*radius;

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

int main() {
    const int H = 500;
    const int W = 500;
    const double timeIncrement = M_PI/100;

    Color white(255, 255, 255);
    Color black;
    Color pixel_color;

    Sphere sphere(Vector(W*0.5, H*0.5, 250), 50);

    double t = 20000;
    double time = 0;
    int imageCounter = 0;
    double tau = 2*M_PI;
    int imageCount = (int)((2*tau)/timeIncrement);
    while (time < tau) {
        Sphere light(Vector(W*0.5, 250+250*std::sin(time), 250+250*std::sin(time-M_PI_2)), 1);
        time += timeIncrement;

        //std::cout << light.center.x << " " << light.center.y << " " << light.center.z << std::endl;

        std::cout << "Rendering: " << imageCounter << " / " << imageCount << std::endl;
        std::ofstream render("images/render" + std::to_string(imageCounter++) + ".ppm");
        render << "P3\n" << W << ' ' << H << ' ' << "255\n";

        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                pixel_color = black;

                Ray ray(Vector(x, y, 0), Vector(0, 0, 1));

                if (sphere.intersects(ray, t)) {
                    Vector intersection_point = ray.origin + ray.direction * t;
                    Vector L = intersection_point - light.center;
                    Vector N = sphere.getNormal(intersection_point);
                    double dt = dot(L.normalize(), N.normalize());

                    pixel_color = white * dt;
                }
                render << (int) pixel_color.r << std::endl
                       << (int) pixel_color.b << std::endl
                       << (int) pixel_color.g << std::endl;
            }
        }
        render.close();
    }
}