#ifndef GPLAY_RABBIT_BVH_H
#define GPLAY_RABBIT_BVH_H
/*
Class BVHNode - A binary tree structured Bounding Volume Hierarchies
reference: https://github.com/RayTracing/raytracing.github.io/blob/release/src/TheNextWeek
The key idea of creating bounding volumes for a set of primitives is to find a volume that fully encloses (bounds) all the objects.
*/

#include <algorithm>
#include "rabbit/hittable.h"

namespace gplay {

namespace rabbit {

class BVHNode : public Hittable {
public:
    BVHNode(HittableList obj_list);

    BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end);

    // Hit respond to the query "does this ray hit you?"
    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    // GetBoundingBox ...
    AxisAlignedBoundingBox GetBoundingBox() const override;

private:
    std::shared_ptr<Hittable> _left;
    std::shared_ptr<Hittable> _right;
    AxisAlignedBoundingBox _bbox;
};

// BoxCompare compare AABBs by axis
bool BoxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis);

// BoxCompareX ...
bool BoxCompareX(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

// BoxCompareY ...
bool BoxCompareY(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

// BoxCompareZ ...
bool BoxCompareZ(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_BVH_H
