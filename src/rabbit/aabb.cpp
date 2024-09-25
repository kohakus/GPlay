#include "aabb.h"

namespace gplay {

namespace rabbit {

AxisAlignedBoundingBox::AxisAlignedBoundingBox() {}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Interval& x, const Interval& y, const Interval& z)
    : x(x), y(y), z(z){
    PadToMinimums();
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Point3& a, const Point3& b) {
    // Treat the two points a and b as extrema for the bounding box
    x = a.X() <= b.X() ? Interval(a.X(), b.X()) : Interval(b.X(), a.X());
    y = a.Y() <= b.Y() ? Interval(a.Y(), b.Y()) : Interval(b.Y(), a.Y());
    z = a.Z() <= b.Z() ? Interval(a.Z(), b.Z()) : Interval(b.Z(), a.Z());
    PadToMinimums();
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const AxisAlignedBoundingBox& bbox_a, const AxisAlignedBoundingBox& bbox_b) {
    x = Interval(bbox_a.x, bbox_b.x);
    y = Interval(bbox_a.y, bbox_b.y);
    z = Interval(bbox_a.z, bbox_b.z);
}

const Interval& AxisAlignedBoundingBox::GetAxisInterval(int axis) const {
    if (axis == 1) { return y; }
    if (axis == 2) { return z; }
    return x;
}

bool AxisAlignedBoundingBox::Hit(const Ray& r, Interval ray_time_interval) const {
    auto&& edp = r.GetEndpoint();
    auto&& dir = r.GetDirection();

    // traverse all three axis to check t-interval overlap
    for (int axis = 0; axis < 3; axis++) {
        auto&& axis_interval = GetAxisInterval(axis);
        double axis_direction_inv = 1.0 / dir[axis];

        double t0 = (axis_interval.GetMin()-edp[axis]) * axis_direction_inv;
        double t1 = (axis_interval.GetMax()-edp[axis]) * axis_direction_inv;

        // deal with corner case: direction component on axis equals zero (contains +infty/-infty)
        if (t0 < t1) {
            // try to shrink interval
            if (t0 > ray_time_interval.GetMin()) { ray_time_interval.SetMin(t0); }
            if (t1 < ray_time_interval.GetMax()) { ray_time_interval.SetMax(t1); }
        } else {
            if (t1 > ray_time_interval.GetMin()) { ray_time_interval.SetMin(t1); }
            if (t0 < ray_time_interval.GetMax()) { ray_time_interval.SetMax(t0); }
        }

        if (ray_time_interval.GetMax() <= ray_time_interval.GetMin()) {
            return false;
        }
    }
    return true;
}

int AxisAlignedBoundingBox::LongestAxis() const {
    if (x.Size() > y.Size()) {
        return x.Size() > z.Size() ? 0 : 2;
    } else {
        return y.Size() > z.Size() ? 1 : 2;
    }
}

void AxisAlignedBoundingBox::PadToMinimums(double delta) {
    if (x.Size() < delta) {
        x = x.Expand(delta);
    }
    if (y.Size() < delta) {
        y = y.Expand(delta);
    }
    if (z.Size() < delta) {
        z = z.Expand(delta);
    }
}

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
