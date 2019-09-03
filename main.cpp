#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <fstream>
#include "src/headers/Sphere.h"
#include "src/headers/Color.h"
#include "src/headers/Light.h"


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

    while (time < TAU) {
        Light red_light(Sphere(Vector(SCREEN_WIDTH*0.5, 250+250*std::sin(time), 250+250*std::sin(time-M_PI_2)), 1),
                        Color::red);
        Light green_light(Sphere(Vector(SCREEN_WIDTH*0.5, 250+250*std::sin(time+2*M_PI/3), 250+250*std::sin(time+2*M_PI/3-M_PI_2)), 1),
                          Color::green);
        Light blue_light(Sphere(Vector(SCREEN_WIDTH*0.5, 250+250*std::sin(time+4*M_PI/3), 250+250*std::sin(time+4*M_PI/3-M_PI_2)), 1),
                          Color::white);

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

                    pixel_color = red_light.getIntensity(intersection_point, normal) +
                                  green_light.getIntensity(intersection_point, normal) +
                                  blue_light.getIntensity(intersection_point, normal);
                }

                render << (int)pixel_color.r << "\n"
                       << (int)pixel_color.b << "\n"
                       << (int)pixel_color.g << "\n";
            }
        }
        render.close();
    }
}