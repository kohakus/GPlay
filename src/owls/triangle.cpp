#include "owls/triangle.h"

namespace gplay {

namespace owls {

Triangle::Triangle() {}

Triangle::Triangle(const gmath::Point3& p0, const gmath::Point3& p1, const gmath::Point3& p2) {
    // precompute reciprocal of vertex z-coordinate for later interpolation
    p0_raster = gmath::Point3(p0.X(), p0.Y(), 1/p0.Z());
    p1_raster = gmath::Point3(p1.X(), p1.Y(), 1/p1.Z());
    p2_raster = gmath::Point3(p2.X(), p2.Y(), 1/p2.Z());

    _quad_area = PinedaEdgeFunction(p0_raster, p1_raster, p2_raster);

    // get bbox corner of the triangle
    _bbox_xmin = Min3(p0_raster.X(), p1_raster.X(), p2_raster.X());
    _bbox_xmax = Max3(p0_raster.X(), p1_raster.X(), p2_raster.X());
    _bbox_ymin = Min3(p0_raster.Y(), p1_raster.Y(), p2_raster.Y());
    _bbox_ymax = Max3(p0_raster.Y(), p1_raster.Y(), p2_raster.Y());
}

bool Triangle::GetBarycentricCoordinate(const gmath::Point3& p, gmath::Point3& w, double& depth) const {
    double w0 = PinedaEdgeFunction(p1_raster, p2_raster, p);
    double w1 = PinedaEdgeFunction(p2_raster, p0_raster, p);
    double w2 = PinedaEdgeFunction(p0_raster, p1_raster, p);

    // check if the sample point within the triangle
    if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
        w = gmath::Point3(w0, w1, w2) / _quad_area;

        // interpolation of 1/z using barycentric coordinates
        double one_over_depth = p0_raster.Z() * w.X() + p1_raster.Z() * w.Y() + p2_raster.Z() * w.Z();
        depth = 1 / one_over_depth;

        return true;
    }

    // sample point outside the triangle
    return false;
}

double Triangle::GetArea() const {
    return _quad_area / 2;
}

gmath::Point2 Triangle::GetBoundingBoxMin() const {
    return gmath::Point2(_bbox_xmin, _bbox_ymin);
}

gmath::Point2 Triangle::GetBoundingBoxMax() const {
    return gmath::Point2(_bbox_xmax, _bbox_ymax);
}

bool Triangle::IsOutOfScreen(int width, int height) const {
    if (_bbox_xmin > width-1 || _bbox_xmax < 0 || _bbox_ymin > height-1 || _bbox_ymax < 0) {
        return true;
    }
    return false;
}

double Triangle::PinedaEdgeFunction(const gmath::Point3& p0, const gmath::Point3& p1, const gmath::Point3& p2) {
    // use clockwise winding (the order in which the vertices that make up the triangles are defined)
    //         P1
    //       /  |
    //    P0  - P2

    auto p0p2 = DeriveVec2FromVec3(p2) - DeriveVec2FromVec3(p0);
    auto p0p1 = DeriveVec2FromVec3(p1) - DeriveVec2FromVec3(p0);
    return Vec2Cross(p0p2, p0p1);
}

VertexVec3Attribute PerspectiveCorrectInterpVec3(const Triangle& triangle, const gmath::Point3& w, double pdepth,
                                                 const VertexVec3Attribute& p0_attr, const VertexVec3Attribute& p1_attr, const VertexVec3Attribute& p2_attr) {
    // first we divide attributes by their z-coordinate
    // (though we use a multiplication here because of the precomputation)
    gmath::Vec3 attr0 = p0_attr.GetVec3Rep() * triangle.p0_raster.Z();
    gmath::Vec3 attr1 = p1_attr.GetVec3Rep() * triangle.p1_raster.Z();
    gmath::Vec3 attr2 = p2_attr.GetVec3Rep() * triangle.p2_raster.Z();
    gmath::Vec3 interp_res = attr0 * w.X() + attr1 * w.Y() + attr2 * w.Z();

    // after interpolation, multipy its own depth to get attribute result
    interp_res *= pdepth;

    return VertexVec3Attribute(interp_res);
}

} // namespace owls

} // namespace gplay
