#ifndef GPLAY_GMATH_VEC3_H
#define GPLAY_GMATH_VEC3_H
/*
The Vec3 class. (not homogeneous coordinate)
To express a 3D vector or RGB-color.
*/

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace gplay {

namespace gmath {

class Vec3 {
public:
    Vec3();
    Vec3(double e0, double e1, double e2);

    inline double X() const { return e[0]; }
    inline double Y() const { return e[1]; }
    inline double Z() const { return e[2]; }

    inline double R() const { return e[0]; }
    inline double G() const { return e[1]; }
    inline double B() const { return e[2]; }

    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    inline double operator[](int i) const { return e[i]; }
    inline double& operator[](int i) { return e[i]; }

    Vec3& operator+=(const Vec3& v2);
    Vec3& operator-=(const Vec3& v2);
    Vec3& operator*=(const Vec3& v2);
    Vec3& operator/=(const Vec3& v2);

    Vec3& operator*=(const double t);
    Vec3& operator/=(const double t);

    // IsNearZero return true if the vector is close to zero in all dimensions
    bool IsNearZero() const;

    inline double LengthSquared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline double Length() const {
        return std::sqrt(LengthSquared());
    }

    inline void ToUnitVec() {
        double k = 1.0 / Length();
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }

public:
    double e[3];
};

// Point3 alias of Vec3
using Point3 = Vec3;

// Color alias of Vec3
using Color = Vec3;

inline std::istream& operator>>(std::istream& is, Vec3& t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, Vec3& t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator/(const Vec3& v, double t) {
    return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline double Vec3Dot(const Vec3& v1, const Vec3& v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 Vec3Cross(const Vec3& v1, const Vec3& v2) {
    return Vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
                -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
                (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline Vec3 UnitVec(const Vec3& v) {
    return v / v.Length();
}

} // namespace gmath

} // namespace gplay

#endif // GPLAY_GMATH_VEC3_H
