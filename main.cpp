#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <fstream>
#include "src/objects/Color.h"
#include "src/objects/Sphere.h"


const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const double TAU = 2*M_PI;
const double TIME_INCREMENT = M_PI/100;

const int imageCount = (int)(TAU/TIME_INCREMENT) + 1;

int main() {
    // objects in screen
    Sphere sphere(Vector(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, 250), 50);

    double solution = 20000;
    double time = 0;
    int imageCounter = 0;
    Color pixel_color;

    while (time < 0.01) {
        Sphere red_light(Vector(SCREEN_WIDTH*0.5, 250+250*std::sin(time), 250+250*std::sin(time-M_PI_2)), 1);
        Sphere green_light(Vector(SCREEN_WIDTH*0.5, 250+250*std::sin(time+M_PI/3), 250+250*std::sin(time+M_PI/3-M_PI_2)), 1);
        Sphere blue_light(Vector(SCREEN_WIDTH*0.5, 250+250*std::sin(time+2*M_PI/3), 250+250*std::sin(time+2*M_PI/3-M_PI_2)), 1);

        time += TIME_INCREMENT;

        std::cout << "Rendering: " << imageCounter << " / " << imageCount << std::endl;
        std::ofstream render("images/render" + std::to_string(imageCounter++) + ".ppm");
        render << "P3\n" << SCREEN_WIDTH << ' ' << SCREEN_HEIGHT << ' ' << "255\n";

        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                pixel_color = Color::black;

                // a ray going from some pixel on the camera view screen towards the z-direction
                Ray ray(Vector(x, y, 0), Vector(0, 0, 1));

                if (sphere.intersects(ray, solution)) {
                    Vector intersection_point = ray.origin + ray.direction * solution;

                    Vector normal = sphere.getNormal(intersection_point);

                    Vector normRedVec = (intersection_point - red_light.center).normalize();
                    Vector normBlueVec = (intersection_point - blue_light.center).normalize();
                    Vector normGreenVec = (intersection_point - green_light.center).normalize();

                    pixel_color = (Color::blue * (int)normBlueVec.dot(normal)) + (Color::red * (int)normRedVec.dot(normal)) + (Color::green * (int)normGreenVec.dot(normal));
                }

                render << (int) pixel_color.r << std::endl
                       << (int) pixel_color.b << std::endl
                       << (int) pixel_color.g << std::endl;
            }
        }
        render.close();
    }
}