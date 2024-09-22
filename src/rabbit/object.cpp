#include "rabbit/object.h"

namespace gplay {

namespace rabbit {

Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> material)
    : _center(center, Vec3(0,0,0)),
      _radius(std::fmax(0,radius)),
      _material(material) {
    Point3 corner_offset = Point3(_radius, _radius, _radius);
    _bbox = AxisAlignedBoundingBox(center-corner_offset, center+corner_offset);
}

Sphere::Sphere(const Point3& center1, const Point3& center2, double radius, std::shared_ptr<Material> material)
    : _center(center1, center2-center1),
      _radius(std::fmax(0,radius)),
      _material(material) {
    Point3 corner_offset = Point3(_radius, _radius, _radius);
    AxisAlignedBoundingBox bbox1(_center.AtPos(0)-corner_offset, _center.AtPos(0)+corner_offset);
    AxisAlignedBoundingBox bbox2(_center.AtPos(1)-corner_offset, _center.AtPos(1)+corner_offset);
    _bbox = AxisAlignedBoundingBox(bbox1, bbox2);
}

bool Sphere::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    // -- Ray-Sphere Intersection --
    // t^2 \mathbf{d} \cdot \mathbf{d}
    //   - 2t \mathbf{d} \cdot (\mathbf{C} - \mathbf{O})
    //   + (\mathbf{C} - \mathbf{O}) \cdot (\mathbf{C} - \mathbf{O}) - r^2 = 0

    Point3 curr_center = _center.AtPos(r.GetTime());
    Vec3 oc = curr_center - r.GetEndpoint();
    // let b = -2h
    double h = Vec3Dot(r.GetDirection(), oc);
    double c = oc.LengthSquared() - _radius*_radius;
    double a = r.GetDirection().LengthSquared();

    // quadratic root: \frac{-b\pm\sqrt{b^2-4ac}}{2a} => \frac{h\pm\sqrt{h^2-ac}}{a}
    double discriminant = h*h - a*c;
    if (discriminant < 0) {
        return false;
    }

    double sqrtd = std::sqrt(discriminant);
    double root = (h-sqrtd) / a;

    // find the nearest root that lies in the acceptable range
    if (!ray_time_interval.Surrounds(root)) {
        root = (h+sqrtd) / a;
        if (!ray_time_interval.Surrounds(root)) {
            return false;
        }
    }

    record.t = root;
    record.hitpoint = r.AtPos(root);
    record.material = _material;
    Vec3 outward_normal = (record.hitpoint - curr_center) / _radius;
    record.SetFaceNormal(r, outward_normal);
    GetSphereUV(outward_normal, record.u, record.v);

    return true;
}

AxisAlignedBoundingBox Sphere::GetBoundingBox() const {
    return _bbox;
}

void Sphere::GetSphereUV(const Point3& p, double& u, double& v) {
    // p: a given point on the sphere of radius one, centered at the origin
    // u: returned value [0,1] of angle around the Y axis from X=-1 (\phi \rightarrow u)
    // v: returned value [0,1] of angle from Y=-1 to Y=+1 (\theta \rightarrow v)
    // theta: the angle up from the bottom pole (that is, up from -Y)
    // phi: the angle around the Y-axis (from -X to +Z to +X to -Z back to -X)
    // sphere coordinate -> cartesian coordinate:
    //   y = -\cos{\theta}
    //   x = -\cos{\phi}\sin{\theta}
    //   z = \sin{\phi}\sin{\theta}

    auto theta = std::acos(-p.Y());
    auto phi = std::atan2(-p.Z(), p.X()) + kPI;
    u = phi / (2*kPI);
    v = theta / kPI;
}

} // namespace rabbit

} // namespace gplay
