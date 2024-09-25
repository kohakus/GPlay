#ifndef GPLAY_RABBIT_OBJECT_H
#define GPLAY_RABBIT_OBJECT_H
/*
Various objects
reference: https://github.com/RayTracing/raytracing.github.io/blob/release/src/TheNextWeek
*/

#include "rabbit/hittable.h"
#include "rabbit/texture.h"

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
    // Sphere center for stationary/moving sphere
    Ray _center;
    // Sphere radius
    double _radius;
    std::shared_ptr<Material> _material;
    AxisAlignedBoundingBox _bbox;
};

class Quadrilateral : public Hittable {
public:
    Quadrilateral(const Point3& q, const Vec3& u, const Vec3& v, std::shared_ptr<Material> material);

    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    AxisAlignedBoundingBox GetBoundingBox() const override;

public:
    // IsInterior determine if the ray-plane intersection point is inside the quadrilateral
    virtual bool IsInterior(double alpha, double beta, HitRecord& record) const;

private:
    // The starting corner of quadrilateral
    Point3 _q;
    // A vector representing the first side
    Vec3 _u;
    // A vector representing the second side
    Vec3 _v;
    // A constant for the plane's basis frame \frac{\mathbf{n}}{\mathbf{n} \cdot \mathbf{n}}
    Vec3 _w;

    // Plane normal unit vector
    Vec3 _normal;
    // D parameter for plane
    double _d;

    std::shared_ptr<Material> _material;
    AxisAlignedBoundingBox _bbox;
};

class Box : public Hittable {
public:
    // Box The 3D box (six sides) that contains the two opposite vertices a and b
    Box(const Point3& a, const Point3& b, std::shared_ptr<Material> material);

    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    AxisAlignedBoundingBox GetBoundingBox() const override;

private:
    std::shared_ptr<Material> _material;
    std::shared_ptr<HittableList> _boundary;
};

class ObjectTranslated : public Hittable {
public:
    ObjectTranslated(std::shared_ptr<Hittable> object, const Vec3& offset);

    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    AxisAlignedBoundingBox GetBoundingBox() const override;

private:
    std::shared_ptr<Hittable> _object;
    Vec3 _offset;
    AxisAlignedBoundingBox _bbox;
};

class ObjectYRotated : public Hittable {
public:
    ObjectYRotated(std::shared_ptr<Hittable> object, double angle);

    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    AxisAlignedBoundingBox GetBoundingBox() const override;
private:
    std::shared_ptr<Hittable> _object;
    double _sin_theta;
    double _cos_theta;
    AxisAlignedBoundingBox _bbox;
};

class ObjectWithConstDensityMedium : public Hittable {
public:
    ObjectWithConstDensityMedium(std::shared_ptr<Hittable> boundary, double density, std::shared_ptr<Texture> texture);

    ObjectWithConstDensityMedium(std::shared_ptr<Hittable> boundary, double density, const Color& albedo);

    bool Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const override;

    AxisAlignedBoundingBox GetBoundingBox() const override;

private:
    double _neg_inv_density;
    std::shared_ptr<Hittable> _boundary;
    std::shared_ptr<Material> _phase_function;
};

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_OBJECT_H
