#ifndef GPLAY_RABBIT_HITTABLE_H
#define GPLAY_RABBIT_HITTABLE_H

/*
Class Hittable - Abstract class for anything a ray might hit
reference: https://github.com/RayTracing/raytracing.github.io/blob/release/src/TheNextWeek
*/

#include <vector>
#include "rabbit/aabb.h"

namespace gplay {

namespace rabbit {

class Material;

class HitRecord {
public:
    // SetFaceNormal sets the hit record normal vector
    void SetFaceNormal(const Ray& r, const Vec3& outward_normal);

    // IsFrontFace ...
    inline bool IsFrontFace() const {
        return _is_front_face;
    }

    // SetFrontFace ...
    inline void SetFrontFace() {
        _is_front_face = true;
    }

    // GetHitTime ...
    inline double GetHitTime() const {
        return t;
    }

public:
    Point3 hitpoint;
    Vec3 normal;
    std::shared_ptr<Material> material;

    // Hit time
    double t;
    // Texture coordinate u
    double u;
    // Texture coordinate u
    double v;

private:
    bool _is_front_face;
};

class Hittable {
public:
    virtual ~Hittable() = default;

    // Hit ray-object intersection
    virtual bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const = 0;

    virtual AxisAlignedBoundingBox GetBoundingBox() const = 0;
};

class HittableList : public Hittable {
public:
    HittableList();
    HittableList(std::shared_ptr<Hittable> obj);

    void ClearAllObjects();

    void AddObject(std::shared_ptr<Hittable> obj);

    size_t Size();

    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    AxisAlignedBoundingBox GetBoundingBox() const override;

public:
    std::vector<std::shared_ptr<Hittable>> objs;

private:
    AxisAlignedBoundingBox _bbox;
};

} // namespace rabbit

} // namespace gplay


#endif // GPLAY_RABBIT_HITTABLE_H
