#ifndef GPLAY_RABBIT_MATHTOOLS_H
#define GPLAY_RABBIT_MATHTOOLS_H
/*
Math tools - Utility Functions
reference: https://github.com/RayTracing/raytracing.github.io/blob/release/src/TheNextWeek
*/

#include <random>
#include "rabbit/vec3.h"

namespace gplay {

namespace rabbit {

// Constant numeric double infinity
const double kInfinity = std::numeric_limits<double>::infinity();
// Constant numeric PI
const double kPI = 3.1415926535897932385;

class Interval {
public:
    Interval();

    Interval(double min, double max);

    Interval(const Interval& a, const Interval& b);

    inline double Size() const {
        return _max - _min;
    }

    inline bool Contains(double x) const {
        return _min <= x && x <= _max;
    }

    inline bool Surrounds(double x) const {
        return _min < x && x < _max;
    }

    inline double Clamp(double x) const {
        if (x < _min) { return _min; }
        if (x > _max) { return _max; }
        return x;
    }

    inline Interval Expand(double delta) const {
        auto padding = delta/2.0;
        return Interval(_min - padding, _max + padding);
    }

    inline double GetMin() const {
        return _min;
    }

    inline double GetMax() const {
        return _max;
    }

    inline void SetMin(double val) {
        _min = val;
    }

    inline void SetMax(double val) {
        _max = val;
    }

public:
    static const Interval empty;
    static const Interval universe;

private:
    double _min;
    double _max;
};

const Interval Interval::empty    = Interval(+kInfinity, -kInfinity);
const Interval Interval::universe = Interval(-kInfinity, +kInfinity);

Interval operator+(const Interval& ival, double displacement) {
    return Interval(ival.GetMin()+displacement, ival.GetMax()+displacement);
}

Interval operator+(double displacement, const Interval& ival) {
    return ival + displacement;
}

inline float FFMin(float a, float b) {
    return a < b ? a : b;
}

inline float FFmax(float a, float b) {
    return a > b ? a : b;
}

// DegreesToRadians ...
inline double DegreesToRadians(double degrees) {
    return degrees * kPI / 180.0;
}

// RandomDouble returns a random real in [0,1).
inline double RandomDouble() {
    // return std::rand() / (RAND_MAX + 1.0);

    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// RandomDouble returns a random real in [min,max).
inline double RandomDouble(double min, double max) {
    return min + (max-min) * RandomDouble();
}

// RandomInt returns a random integer in [min,max].
inline int RandomInt(int min, int max) {
    return int(RandomDouble(min, max+1));
}

inline Vec3 RandomVec3() {
    return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
}

inline Vec3 RandomVec3(double min, double max) {
    return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
}

// RandomPointInUnitDisk returns a random point in the unit disk centered at the origin
Point3 RandomPointInUnitDisk();

// RandomPointInDisk returns a random point in the disk with specific radius centered at the origin
Point3 RandomPointInDisk(double radius);

// RandomPointInUnitSquare returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square
Point3 RandomPointInUnitSquare();

// RandomUnitVec3 return random vector on the surface of the unit sphere
Vec3 RandomUnitVec3();

// ReflectVec3 mirrored reflection
Vec3 ReflectVec3(const Vec3& v, const Vec3& n);

// RefractVec3 refraction described by Snell's Law
Vec3 RefractVec3(const Vec3& uv, const Vec3& n, double eta_ratio);

// Fresnel fresnel equations describing reflection and refraction of light
double Fresnel(double cosi, double cost, double etai, double etat);

// SchlickApprox schlick's polynomial approximation for fresnel equation
double SchlickApprox(double cosine, double refractive_index);

// TrilinearInterp trilinear interpolation
double TrilinearInterp(double c[2][2][2], double u, double v, double w);

// PerlinInterp trilinear perlin interpolation
double PerlinInterp(Vec3 c[2][2][2], double u, double v, double w);

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_MATHTOOLS_H
