#ifndef GPLAY_OWLS_MATHTOOLS_H
#define GPLAY_OWLS_MATHTOOLS_H
/*
Math tools - Utility Functions
*/

#include <algorithm>
#include <cmath>

#include "gmath/smatrix4.h"
#include "gmath/vec3.h"
#include "gmath/vec2.h"

namespace gplay {

namespace owls {

// Constant Inch to Millimeter ratio
const double kInchToMm = 25.4;
// Constant numeric PI
const double kPI = 3.1415926535897932385;

// Min3 ...
inline double Min3(const double &a, const double &b, const double &c) {
    return std::min(a, std::min(b, c));
}

// Max3 ...
inline double Max3(const double &a, const double &b, const double &c) {
    return std::max(a, std::max(b, c));
}

// DegreesToRadians ...
inline double DegreesToRadians(double degrees) {
    return degrees * kPI / 180.0;
}

// RadiansToDegrees ...
inline double RadiansToDegrees(double radians) {
    return radians * 180.0 / kPI;
}

// DeriveVec2FromVec3 ...
gmath::Vec2 DeriveVec2FromVec3(const gmath::Vec3& v);

} // namespace owls

} // namespace gplay

#endif // GPLAY_OWLS_MATHTOOLS_H
