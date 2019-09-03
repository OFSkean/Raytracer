cmake_minimum_required(VERSION 3.14)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer main.cpp src/objects/Vector.h src/objects/Ray.h src/objects/Sphere.h src/objects/Color.h)