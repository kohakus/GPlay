#ifndef GPLAY_RABBIT_DRAW_H
#define GPLAY_RABBIT_DRAW_H

#include "rabbit/mathtools.h"

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
void WriteColor(std::ostream& out, const Color& pixel_color) {
    // Apply a linear to gamma transform for gamma 2
    auto r = LinearToGamma(pixel_color.R());
    auto g = LinearToGamma(pixel_color.G());
    auto b = LinearToGamma(pixel_color.B());

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity(0.000, 0.999);
    int rbyte = static_cast<int>(256 * intensity.Clamp(r));
    int gbyte = static_cast<int>(256 * intensity.Clamp(g));
    int bbyte = static_cast<int>(256 * intensity.Clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_DRAW_H
