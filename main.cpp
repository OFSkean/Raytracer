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


double dot(Vector a, Vector b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

struct Color {
    short r, b, g;
    Color() {r=g=b=0;}
    Color(short R, short B, short G) {r=R; b=B; g=G;}
};

struct Ray {
    Vector origin;
    Vector direction;
    Ray(Vector a, Vector b) {origin=a; direction=b;}
};

struct Sphere {
    Vector center;
    double radius;
    Sphere() {center=Vector(); radius=1;}    //unit sphere
    Sphere(Vector c, double r) {center=c; radius=r;}

    Vector getNormal(Vector v) {
        return (v - center) / radius;
    }
    bool intersects(Ray ray, double &t) {
        Vector oc = ray.origin - center;

        double disc_a = 1;    // a = dot(ray.dest, ray.dest) = 1
        double disc_b = 2*dot(oc, ray.direction);
        double disc_c = 1 - radius*radius;

        double discriminant = disc_b*disc_b - 4*disc_a*disc_c;
        if (discriminant < 0) {
            return false;
        }
        else {
            discriminant = sqrt(discriminant);
            double t0 = -disc_b + discriminant;
            double t1 = -disc_b - discriminant;
            t = (t0 < t1) ? t0 : t1;
            return true;
        }
    }
};

void saturate(Vector& color) {
    color.x = (color.x > 255) ? 255 : (color.x < 0) ? 0 : color.x;
    color.y = (color.y > 255) ? 255 : (color.y < 0) ? 0 : color.y;
    color.z = (color.z > 255) ? 255 : (color.z < 0) ? 0 : color.z;
}
int main() {
    const int H = 500;
    const int W = 500;

    Vector white(255, 255, 255);
    Vector black(0, 0, 0);
    Vector red(255, 0, 0);

    Sphere sphere(Vector(W*0.5, H*0.5, 50), 50);
    Sphere light(Vector(0, 0, 5), 1);
    Vector camera(Vector(0, 0, 1));

    std::ofstream render("render.ppm");
    render << "P3\n" << W << ' ' << H << ' ' << "255\n";

    double t;
    Vector pixel_color(black);

    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            pixel_color = black;

            Ray ray(Vector(x, y, 0), camera);

            if (sphere.intersects(ray, t)) {
                Vector extended = ray.origin + ray.direction*t;
                Vector L = light.center - extended;
                Vector N = sphere.getNormal(extended);
                double dt = dot(L.normalize(), N.normalize());

                pixel_color = (red + white*dt) * 0.5;
                saturate(pixel_color);
            }
            render << (int)pixel_color.x << ' '
                   << (int)pixel_color.y << ' '
                   << (int)pixel_color.z << '\n';
        }
    }
}