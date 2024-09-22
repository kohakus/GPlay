#include "rabbit/vec3.h"

namespace gplay {

namespace rabbit {

Vec3::Vec3() : e{0, 0, 0} {}

Vec3::Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

Vec3& Vec3::operator+=(const Vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

Vec3& Vec3::operator*=(const Vec3& v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

Vec3& Vec3::operator/=(const Vec3& v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

Vec3& Vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vec3& Vec3::operator/=(const double t) {
    return *this *= 1.0/t;
}

bool Vec3::IsNearZero() const {
    return (std::fabs(e[0]) < 1e-8) && (std::fabs(e[1]) < 1e-8) && (std::fabs(e[2]) < 1e-8);
}

} // namespace rabbit

} // namespace gplay
