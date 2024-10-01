#ifndef GPLAY_OWLS_TRIANGLE_H
#define GPLAY_OWLS_TRIANGLE_H
/*
Class Triangle
*/

#include "owls/vattr.h"

namespace gplay {

namespace owls {

// Triangle triangle defined under raster space
class Triangle {
public:
    Triangle();

    Triangle(const gmath::Point3& p0, const gmath::Point3& p1, const gmath::Point3& p2);

    // GetBarycentricCoordinate compute the representation of barycentric coordinate of a sample point whthin the triangle
    // P = \lambda_0 \cdot V0 + \lambda_1 \cdot V1 + \lambda_2 \cdot V2
    // return false if the sample point P outside the triangle
    bool GetBarycentricCoordinate(const gmath::Point3& p, gmath::Point3& w, double& depth) const;

    // GetArea return the area of triangle
    double GetArea() const;

    // GetBoundingBoxMin ...
    gmath::Point2 GetBoundingBoxMin() const;

    // GetBoundingBoxMax ...
    gmath::Point2 GetBoundingBoxMax() const;

    // IsOutOfRange test if the whole triangle is out of a specific range, usually screen (test by bbox)
    bool IsOutOfScreen(int width, int height) const;

private:
    // PinedaEdgeFunction determine if a pixel (or the point at the center of the pixel) is within a triangle's edges
    // points contained within the triangle are all located to the right of all three edges of the triangle
    static double PinedaEdgeFunction(const gmath::Point3& p0, const gmath::Point3& p1, const gmath::Point3& p2);

public:
    gmath::Point3 p0_raster;
    gmath::Point3 p1_raster;
    gmath::Point3 p2_raster;

private:
    // Quadrilateral area corresponds to triangle, i.e. 2 \times triangle area
    double _quad_area;
    double _bbox_xmin, _bbox_ymin;
    double _bbox_xmax, _bbox_ymax;
};

// PerspectiveCorrectInterpVec3 perspective-correct interpolation for vertex vec3 attribute
VertexVec3Attribute PerspectiveCorrectInterpVec3(const Triangle& triangle, const gmath::Point3& w, double pdepth,
                                                 const VertexVec3Attribute& p0_attr, const VertexVec3Attribute& p1_attr, const VertexVec3Attribute& p2_attr);

} // namespace owls

} // namespace gplay

#endif // GPLAY_OWLS_TRIANGLE_H
