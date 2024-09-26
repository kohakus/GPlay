#include "rabbit/bvh.h"

namespace gplay {

namespace rabbit {

BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end) {
    // -- Build BVH Tree --
    // the key point is splitting bvh volumes:
    // 1. randomly choose an axis
    //   1.1 optimization: Instead of choosing a random splitting axis,
    //                     split the longest axis of the enclosing bounding box to get the most subdivision
    // 2. sort the primitives
    // 3. put half in each subtree

    // int axis = RandomInt(0, 2);

    _bbox = AxisAlignedBoundingBox::empty;
    for (size_t obj_idx = start; obj_idx < end; obj_idx++) {
        _bbox = AxisAlignedBoundingBox(_bbox, objects[obj_idx]->GetBoundingBox());
    }
    int axis = _bbox.LongestAxis();

    size_t list_span = end - start;
    if (list_span == 1) {
        // just have one element, duplicate it in each subtree (leaf)
        _left = _right = objects[start];
    } else if (list_span == 2) {
        // two elements, put one in each subtree (leaf)
        _left = objects[start];
        _right = objects[start+1];
    } else {
        // auto comparator = [axis](const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
        //     return BoxCompare(a, b, axis);
        // };

        auto comparator = (axis == 0) ? BoxCompareX
                        : (axis == 1) ? BoxCompareY
                                      : BoxCompareZ;
        std::sort(objects.begin()+start, objects.begin()+end, comparator);
        size_t mid = start + list_span/2;

        // build bvh recursively
        _left = std::make_shared<BVHNode>(objects, start, mid);
        _right = std::make_shared<BVHNode>(objects, mid, end);
    }
}

BVHNode::BVHNode(HittableList obj_list) : BVHNode(obj_list.objs, 0, obj_list.Size()) {}

bool BVHNode::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    if (!_bbox.Hit(r, ray_time_interval)) {
        return false;
    }
    bool hit_left = _left->Hit(r, ray_time_interval, record);
    bool hit_right = _right->Hit(r, Interval(ray_time_interval.GetMin(),
                                             hit_left ? record.GetHitTime() : ray_time_interval.GetMax()),
                                 record);
    return hit_left || hit_right;
}

AxisAlignedBoundingBox BVHNode::GetBoundingBox() const {
    return _bbox;
}

bool BoxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) {
    auto&& a_axis_interval = a->GetBoundingBox().GetAxisInterval(axis);
    auto&& b_axis_interval = b->GetBoundingBox().GetAxisInterval(axis);
    return a_axis_interval.GetMin() < b_axis_interval.GetMin();
}

bool BoxCompareX(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return BoxCompare(a, b, 0);
}

bool BoxCompareY(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return BoxCompare(a, b, 1);
}

bool BoxCompareZ(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
    return BoxCompare(a, b, 2);
}

} // namespace rabbit

} // namespace gplay
