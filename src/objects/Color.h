//
// Created by ofsk222 on 9/2/2019.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include <algorithm>

struct Color {
    int r, g, b;
    Color() {r=g=b=0;}  //default to black
    Color (int R, int B, int G) {r=R; g=G; b=B;}

    //
    // operations should saturate so that values don't over/underflow
    //

    Color operator * (int d) const {
        if (d > 0) {
            return { std::min(d*r, 255), std::min(d*g, 255),  std::min(d*b, 255) } ;
        }
        else {
            return {0, 0, 0};
        }
    }
    Color operator + (Color c) const {
        return { std::min(r+c.r, 255), std::min(g+c.g, 255), std::min(b+c.b, 255) };
    }

    static const Color red;
    static const Color green;
    static const Color blue;
    static const Color white;
    static const Color black;
};

const Color Color::red(255, 0, 0);
const Color Color::green(0, 255, 0);
const Color Color::blue(0, 0, 255);
const Color Color::white(255, 255, 255);
const Color Color::black(0, 0, 0);
#endif //RAYTRACER_COLOR_H
