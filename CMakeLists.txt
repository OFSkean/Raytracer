cmake_minimum_required(VERSION 3.14)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer main.cpp src/headers/Vector.h src/headers/Ray.h src/headers/Sphere.h src/headers/Color.h)