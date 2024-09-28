#ifndef GPLAY_GMATH_VEC2_H
#define GPLAY_GMATH_VEC2_H
/*
The Vec2 class. (not homogeneous coordinate)
*/

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace gplay {

namespace gmath {

class Vec2 {
public:
    Vec2();
    Vec2(double e0, double e1);

    inline double X() const { return e[0]; }
    inline double Y() const { return e[1]; }

    inline const Vec2& operator+() const { return *this; }
    inline Vec2 operator-() const { return Vec2(-e[0], -e[1]); }
    inline double operator[](int i) const { return e[i]; }
    inline double& operator[](int i) { return e[i]; }

    Vec2& operator+=(const Vec2& v2);
    Vec2& operator-=(const Vec2& v2);
    Vec2& operator*=(const Vec2& v2);
    Vec2& operator/=(const Vec2& v2);

    Vec2& operator*=(const double t);
    Vec2& operator/=(const double t);

    inline double LengthSquared() const {
        return e[0] * e[0] + e[1] * e[1];
    }

    inline double Length() const {
        return std::sqrt(LengthSquared());
    }

    inline void ToUnitVec() {
        double k = 1.0 / Length();
        e[0] *= k;
        e[1] *= k;
    }

public:
    double e[2];
};

inline std::istream& operator>>(std::istream& is, Vec2& t) {
    is >> t.e[0] >> t.e[1];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, Vec2& t) {
    os << t.e[0] << " " << t.e[1];
    return os;
}

inline Vec2 operator+(const Vec2& v1, const Vec2& v2) {
    return Vec2(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
}

inline Vec2 operator-(const Vec2& v1, const Vec2& v2) {
    return Vec2(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
}

inline Vec2 operator*(const Vec2& v1, const Vec2& v2) {
    return Vec2(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1]);
}

inline Vec2 operator/(const Vec2& v1, const Vec2& v2) {
    return Vec2(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1]);
}

inline Vec2 operator*(double t, const Vec2& v) {
    return Vec2(t * v.e[0], t * v.e[1]);
}

inline Vec2 operator*(const Vec2& v, double t) {
  return t * v;
}

inline Vec2 operator/(const Vec2& v, double t) {
    return Vec2(v.e[0] / t, v.e[1] / t);
}

inline double Vec2Dot(const Vec2& v1, const Vec2& v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1];
}

// Note that this is not actual cross product.
// 2D cross returns the magnitude of the vector that would result from a regular 3D cross product of the input vectors.
inline double Vec2Cross(const Vec2& v1, const Vec2& v2) {
  return v1.X()*v2.Y() - v1.X()*v2.Y();
}

inline Vec2 UnitVec(const Vec2& v) {
  return v / v.Length();
}

} // namespace gmath

} // namespace gplay

#endif // GPLAY_GMATH_VEC2_H
