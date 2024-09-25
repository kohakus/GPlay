#ifndef GPLAY_RABBIT_DRAW_H
#define GPLAY_RABBIT_DRAW_H

#include <fstream>
#include "rabbit/camera.h"
#include "rabbit/material.h"

namespace gplay {

namespace rabbit {

// LinearToGamma transform data from linear space into gamma space, with gamma=2
inline double LinearToGamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }
    return 0;
}

// WriteColor writes a single pixel's color out to the standard output stream
void WriteColor(std::ostream& out, const Color& pixel_color);

// RayColor ...
Color RayColor(const Ray& r, int depth_limit, const Camera& camera, const Hittable& world);

// RenderWorld ...
void RenderWorld(const Camera& camera, const Hittable& world, const std::string& outfile);

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_DRAW_H
