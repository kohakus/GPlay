cmake_minimum_required(VERSION 3.15.0)
project(GPlayProjects)

add_executable(gplay_rabbit rabbit/main.cpp
    gmath/vec3.cpp
    rabbit/vec3.cpp
    rabbit/ray.cpp
    rabbit/mathtools.cpp
    rabbit/camera.cpp
    rabbit/hittable.cpp
    rabbit/aabb.cpp
    rabbit/bvh.cpp
    rabbit/object.cpp
    rabbit/material.cpp
    rabbit/texture.cpp
    rabbit/noise.cpp
    rabbit/draw.cpp
)
target_link_libraries(gplay_rabbit PRIVATE
    stb_image
)

add_executable(gplay_owls owls/main.cpp
    gmath/vec3.cpp
    gmath/vec2.cpp
    gmath/smatrix4.cpp
    owls/mathtools.cpp
    owls/camera.cpp
    owls/triangle.cpp
    owls/vattr.cpp
    owls/transforms.cpp
    owls/shading.cpp
    owls/draw.cpp
)
