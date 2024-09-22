#include "rabbit/hittable.h"

namespace gplay {

namespace rabbit {

void HitRecord::SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
    // NOTE: the parameter `outward_normal` is assumed to have unit length
    _is_front_face = Vec3Dot(r.GetDirection(), outward_normal) < 0;
    normal = _is_front_face ? outward_normal : -outward_normal;
}

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> obj) {
    AddObject(obj);
}

void HittableList::ClearAllObjects() {
    objs.clear();
}

void HittableList::AddObject(std::shared_ptr<Hittable> obj) {
    objs.push_back(obj);
    _bbox = AxisAlignedBoundingBox(_bbox, obj->GetBoundingBox());
}

size_t HittableList::Size() {
    return objs.size();
}

bool HittableList::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    HitRecord tmp_rec;
    bool is_hit = false;
    double curr_closest = ray_time_interval.GetMax();

    // find the closest hit record if exist
    for (const auto& obj : objs) {
        if (obj->Hit(r, Interval(ray_time_interval.GetMin(), curr_closest), tmp_rec)) {
            is_hit = true;
            curr_closest = tmp_rec.GetHitTime();
        }
    }
    if (is_hit) {
        record = tmp_rec;
    }
    return is_hit;
}

AxisAlignedBoundingBox HittableList::GetBoundingBox() const {
    return _bbox;
}

} // namespace rabbit

} // namespace gplay
