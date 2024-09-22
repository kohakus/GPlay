#ifndef GPLAY_RABBIT_AABB_H
#define GPLAY_RABBIT_AABB_H
/*
Class AxisAlignedBoundingBox
reference: https://github.com/RayTracing/raytracing.github.io/blob/release/src/TheNextWeek
*/

#include "rabbit/mathtools.h"
#include "rabbit/ray.h"

namespace gplay {

namespace rabbit {

class AxisAlignedBoundingBox {
public:
    AxisAlignedBoundingBox();

    AxisAlignedBoundingBox(const Interval& x, const Interval& y, const Interval& z);

    AxisAlignedBoundingBox(const Point3& a, const Point3& b);

    AxisAlignedBoundingBox(const AxisAlignedBoundingBox& bbox_a, const AxisAlignedBoundingBox& bbox_b);

    // GetAxisInterval return interval of AABB correspond to specific axis: 0-x 1-y 2-z
    const Interval& GetAxisInterval(int axis) const;

    // Hit test ray intersection with AABB
    // If a ray intersects the box bounded by all pairs of planes, then all 𝑡-intervals will overlap
    bool Hit(const Ray& r, Interval ray_time_interval) const;

    // LongestAxis returns the index of the longest axis of the bounding box
    int LongestAxis() const;

public:
    Interval x;
    Interval y;
    Interval z;

    // empty AABB
    static const AxisAlignedBoundingBox empty;
    // universe AABB
    static const AxisAlignedBoundingBox universe;

private:
    // PadToMinimums adjust the AABB so that no side is narrower than some delta, padding if necessary e.g. flat
    void PadToMinimums(double delta=0.0001);
};

const AxisAlignedBoundingBox AxisAlignedBoundingBox::empty    = AxisAlignedBoundingBox(Interval::empty,    Interval::empty,    Interval::empty);
const AxisAlignedBoundingBox AxisAlignedBoundingBox::universe = AxisAlignedBoundingBox(Interval::universe, Interval::universe, Interval::universe);

AxisAlignedBoundingBox operator+(const AxisAlignedBoundingBox& bbox, const Vec3& offset) {
    return AxisAlignedBoundingBox(bbox.x+offset.X(), bbox.y+offset.Y(), bbox.z+offset.Z());
}

AxisAlignedBoundingBox operator+(const Vec3& offset, const AxisAlignedBoundingBox& bbox) {
    return bbox + offset;
}

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_AABB_H
