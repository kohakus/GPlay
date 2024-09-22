#include "rabbit/texture.h"

namespace gplay {

namespace rabbit {

SolidColor::SolidColor(const Color& albedo) : _albedo(albedo) {}

SolidColor::SolidColor(double red, double green, double blue)
    : _albedo(Color(red, green, blue)) {}

Color SolidColor::Value(double u, double v, const Point3& p) const {
    return _albedo;
}

} // namespace rabbit

} // namespace gplay
