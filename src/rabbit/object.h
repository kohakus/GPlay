#ifndef GPLAY_RABBIT_OBJECT_H
#define GPLAY_RABBIT_OBJECT_H
/*
Various objects
reference: https://github.com/RayTracing/raytracing.github.io/blob/release/src/TheNextWeek
*/

#include "rabbit/hittable.h"

namespace gplay {

namespace rabbit {

class Sphere : public Hittable {
public:
    // Sphere make a stationary sphere
    Sphere(const Point3& center, double radius, std::shared_ptr<Material> material);

    // Sphere make a moving sphere
    Sphere(const Point3& center1, const Point3& center2, double radius, std::shared_ptr<Material> material);

    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    AxisAlignedBoundingBox GetBoundingBox() const override;

private:
    // GetSphereUV takes points on the unit sphere centered at the origin, and computes u and v
    // this function map theta and phi to texture coordinates u and v in [0,1], i.e. Texture mapping for Spheres
    static void GetSphereUV(const Point3& p, double& u, double& v);

private:
    Ray _center;
    double _radius;
    std::shared_ptr<Material> _material;
    AxisAlignedBoundingBox _bbox;
};

class Quadrilateral : public Hittable {

};

class ObjectTranslated : public Hittable {

};

class ObjectYRotated : public Hittable {

};

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_OBJECT_H
