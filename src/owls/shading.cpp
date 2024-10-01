#include "owls/shading.h"

namespace gplay {

namespace owls {

double TriangleFacingRatio(const gmath::Point3& w, const double pdepth, const gmath::SMatrix4& vertices) {
    // triangle vertices (camera space)
    gmath::Point3 p0(vertices[0][0], vertices[0][1], vertices[0][2]);
    gmath::Point3 p1(vertices[1][0], vertices[1][1], vertices[1][2]);
    gmath::Point3 p2(vertices[2][0], vertices[2][1], vertices[2][2]);

    // treat the view direction P-E as a kind of attribute, then interpolate it
    gmath::Vec3 v0 = -p0;
    gmath::Vec3 v1 = -p1;
    gmath::Vec3 v2 = -p2;

    gmath::Vec3 view_direction = (v0/p0.Z()) * w.X() + (v1/p1.Z()) * w.Y() + (v2/p2.Z()) * w.Z();
    view_direction = UnitVec(view_direction * pdepth);

    auto normal = UnitVec(Vec3Cross(p2-p0, p1-p0));

    return std::fmax(0, Vec3Dot(normal, view_direction));
}

double CheckerPatternValue(double u, double v, double scale) {
    double checker = (std::fmod(u * scale, 1.0) > 0.5) ^ (std::fmod(v * scale, 1.0) < 0.5);
    return 0.3 * (1-checker) + 0.7 * checker;
}

double CheckerPatternValue(const VertexUVAttribute& uv_attr, double scale) {
    auto uv = uv_attr.GetVec2Rep();
    return CheckerPatternValue(uv.X(), uv.Y(), scale);
}

} // namespace owls

} // namespace gplay
