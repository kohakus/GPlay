#include "gmath/vec2.h"

namespace gplay {

namespace gmath {

Vec2::Vec2() : e{0, 0} {}

Vec2::Vec2(double e0, double e1) : e{e0, e1} {}

Vec2& Vec2::operator+=(const Vec2& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    return *this;
}

Vec2& Vec2::operator*=(const Vec2& v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    return *this;
}

Vec2& Vec2::operator/=(const Vec2& v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    return *this;
}

Vec2& Vec2::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    return *this;
}

Vec2& Vec2::operator/=(const double t) {
    return *this *= 1.0/t;
}

} // namespace gmath

} // namespace gplay
