#ifndef GPLAY_OWLS_SHADING_H
#define GPLAY_OWLS_SHADING_H

#include "owls/vattr.h"

namespace gplay {

namespace owls {

// TriangleFacingRatio return facing ratio of a point on flat triangle (camera space)
// The facing ratio is the dot product between the triangle normal and the view direction
// The view direction is the vector from a point P on the triangle being shaded to the camera position E(0,0,0)
double TriangleFacingRatio(const gmath::Point3& w, const double pdepth, const gmath::SMatrix4& vertices);

// CheckerPatternValue return checker pattern value of a point in uv space
double CheckerPatternValue(double u, double v, double scale);

// CheckerPatternValue ...
double CheckerPatternValue(const VertexUVAttribute& uv_attr, double scale);

} // namespace owls

} // namespace gplay

#endif // GPLAY_OWLS_SHADING_H
