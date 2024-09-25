#include "rabbit/object.h"
#include "rabbit/material.h"

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
    // sphere coordinate <-> cartesian coordinate:
    //   y = -\cos{\theta}
    //   x = -\cos{\phi}\sin{\theta}
    //   z = \sin{\phi}\sin{\theta}

    auto theta = std::acos(-p.Y());
    auto phi = std::atan2(-p.Z(), p.X()) + kPI;
    u = phi / (2*kPI);
    v = theta / kPI;
}

Quadrilateral::Quadrilateral(const Point3& q, const Vec3& u, const Vec3& v, std::shared_ptr<Material> material)
    : _q(q), _u(u), _v(v) {
    // Plane normal
    Vec3 n = Vec3Cross(_u, _v);
    _normal = UnitVec(n);

    _d = Vec3Dot(_normal, _q);
    _w = n / Vec3Dot(n,n);

    // Compute the bounding box of all four vertices,
    // and combine the resulting two AABBs

    auto bbox1 = AxisAlignedBoundingBox(_q, _q + _u + _v);
    auto bbox2 = AxisAlignedBoundingBox(_q + _u, _q + _v);
    _bbox = AxisAlignedBoundingBox(bbox1, bbox2);
}

bool Quadrilateral::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    // -- Ray-Quadrilateral Intersection --
    //   1. finding the plane that contains that quad
    //   2. solving for the intersection of a ray and the quad-containing plane
    //   3. determining if the hit point lies inside the quad

    // -- Ray-Plane Intersection --
    // Plane: Ax + By + Cz = D
    // \mathbf{n} \cdot ( \mathbf{P} + t \mathbf{d} ) = D, \mathbf{n} = (A,B,C)
    //   => t = \frac{D - \mathbf{n} \cdot \mathbf{P}}{\mathbf{n} \cdot \mathbf{d}}
    //      \mathbf{P}' = \mathbf{P} + t \mathbf{d}

    // -- Deriving the Planar Coordinates --
    // Intersection \mathbf{P}' = \mathbf{Q} + \alpha \mathbf{u} + \beta \mathbf{v}
    //   => \alpha = \mathbf{w} \cdot (\mathbf{p} \times \mathbf{v})
    //      \beta  = \mathbf{w} \cdot (\mathbf{u} \times \mathbf{p})
    //  where \mathbf{p} = \mathbf{P}' - \mathbf{Q}

    // No hit if the ray is parallel to the plane
    double denom = Vec3Dot(_normal, r.GetDirection());
    if (std::fabs(denom) < 1e-8) {
        return false;
    }

    double t = (_d - Vec3Dot(_normal, r.GetEndpoint())) / denom;
    if (!ray_time_interval.Contains(t)) {
        return false;
    }

    Point3 intersection = r.AtPos(t);
    Vec3 q_to_intersection = intersection - _q;
    double alpha = Vec3Dot(_w, Vec3Cross(q_to_intersection, _v));
    double beta = Vec3Dot(_w, Vec3Cross(_u, q_to_intersection));
    if (!IsInterior(alpha, beta, record)) {
        return false;
    }

    record.t = t;
    record.hitpoint = intersection;
    record.material = _material;
    record.SetFaceNormal(r, _normal);
    return true;
}

AxisAlignedBoundingBox Quadrilateral::GetBoundingBox() const {
    return _bbox;
}

bool Quadrilateral::IsInterior(double alpha, double beta, HitRecord& record) const {
    // -- Interior Testing of The Intersection Using Planar Coordinates --
    //  1. 0 <= alpha <= 1
    //  2. 0 <= beta <= 1

    Interval unit_interval = Interval(0, 1);
    if (!unit_interval.Contains(alpha) || !unit_interval.Contains(beta)) {
        return false;
    }
    record.u = alpha;
    record.v = beta;

    return true;
}

Box::Box(const Point3& a, const Point3& b, std::shared_ptr<Material> material)
    : _material(material),
      _boundary(std::make_shared<HittableList>()) {
    Point3 minp = Point3(std::fmin(a.X(), b.X()), std::fmin(a.Y(), b.Y()), std::fmin(a.Z(), b.Z()));
    Point3 maxp = Point3(std::fmax(a.X(), b.X()), std::fmax(a.Y(), b.Y()), std::fmax(a.Z(), b.Z()));

    Vec3 dx = Vec3(maxp.X()-minp.X(), 0, 0);
    Vec3 dy = Vec3(0, maxp.Y()-minp.Y(), 0);
    Vec3 dz = Vec3(0, 0, maxp.Z()-minp.Z());

    _boundary->AddObject(std::make_shared<Quadrilateral>(Point3(minp.X(), minp.Y(), maxp.Z()),  dx,  dy, _material)); // front
    _boundary->AddObject(std::make_shared<Quadrilateral>(Point3(maxp.X(), minp.Y(), maxp.Z()), -dz,  dy, _material)); // right
    _boundary->AddObject(std::make_shared<Quadrilateral>(Point3(maxp.X(), minp.Y(), minp.Z()), -dx,  dy, _material)); // back
    _boundary->AddObject(std::make_shared<Quadrilateral>(Point3(minp.X(), minp.Y(), minp.Z()),  dz,  dy, _material)); // left
    _boundary->AddObject(std::make_shared<Quadrilateral>(Point3(minp.X(), maxp.Y(), maxp.Z()),  dx, -dz, _material)); // top
    _boundary->AddObject(std::make_shared<Quadrilateral>(Point3(minp.X(), minp.Y(), minp.Z()),  dx,  dz, _material)); // bottom
}

bool Box::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    return _boundary->Hit(r, ray_time_interval, record);
}

AxisAlignedBoundingBox Box::GetBoundingBox() const {
    return _boundary->GetBoundingBox();
}

ObjectTranslated::ObjectTranslated(std::shared_ptr<Hittable> object, const Vec3& offset)
    : _object(object),
      _offset(offset){
    // Remember to offset the bounding box,
    // otherwise the incident ray might be looking in the wrong place and trivially reject the intersection
    _bbox = _object->GetBoundingBox() + _offset;
}

bool ObjectTranslated::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    // We don’t actually need to move objects in the scene;
    // Instead we move the rays in the opposite direction

    // Move the ray backwards by the offset
    Ray offset_r(r.GetEndpoint() - _offset, r.GetDirection(), r.GetTime());

    // Determine whether an intersection exists along the offset ray (and if so, where)
    if (!_object->Hit(offset_r, ray_time_interval, record)) {
        return false;
    }

    // Move the intersection point forwards by the offset
    record.hitpoint += _offset;

    return true;
}

AxisAlignedBoundingBox ObjectTranslated::GetBoundingBox() const {
    return _bbox;
}

ObjectYRotated::ObjectYRotated(std::shared_ptr<Hittable> object, double angle) {
    auto radians = DegreesToRadians(angle);
    _sin_theta = std::sin(radians);
    _cos_theta = std::cos(radians);
    _bbox = _object->GetBoundingBox();

    Point3 min( kInfinity,  kInfinity,  kInfinity);
    Point3 max(-kInfinity, -kInfinity, -kInfinity);

    // rotate bounding box's 8 points
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*_bbox.x.GetMax() + (1-i)*_bbox.x.GetMin();
                auto y = j*_bbox.y.GetMax() + (1-j)*_bbox.y.GetMin();
                auto z = k*_bbox.z.GetMax() + (1-k)*_bbox.z.GetMin();

                auto newx =  _cos_theta*x + _sin_theta*z;
                auto newz = -_sin_theta*x + _cos_theta*z;

                Vec3 tester(newx, y, newz);
                for (int c = 0; c < 3; c++) {
                    min[c] = std::fmin(min[c], tester[c]);
                    max[c] = std::fmax(max[c], tester[c]);
                }
            }
        }
    }

    // renew rotated bbox
    _bbox = AxisAlignedBoundingBox(min, max);
}

bool ObjectYRotated::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    // Transform the ray from world space to object space
    // i.e. Move the ray backwards by the offset

    Point3 origin = Point3(
        (_cos_theta * r.GetEndpoint().X()) + (-_sin_theta * r.GetEndpoint().Z()),
        r.GetEndpoint().Y(),
        (_sin_theta * r.GetEndpoint().X()) + (_cos_theta * r.GetEndpoint().Z())
    );

    Vec3 direction = Vec3(
        (_cos_theta * r.GetDirection().X()) + (-_sin_theta * r.GetDirection().Z()),
        r.GetDirection().Y(),
        (_sin_theta * r.GetDirection().X()) + (_cos_theta * r.GetDirection().Z())
    );

    Ray rotated_r(origin, direction, r.GetTime());

    // Determine whether an intersection exists in object space (and if so, where)
    // i.e. Determine whether an intersection exists along the offset ray (and if so, where)

    if (!_object->Hit(rotated_r, ray_time_interval, record)) {
        return false;
    }

    // Transform the intersection from object space back to world space
    // i.e. Move the intersection point forwards by the offset

    record.hitpoint = Point3(
        (_cos_theta * record.hitpoint.X()) + (_sin_theta * record.hitpoint.Z()),
        record.hitpoint.Y(),
        (-_sin_theta * record.hitpoint.X()) + (_cos_theta * record.hitpoint.Z())
    );

    record.normal = Vec3(
        (_cos_theta * record.normal.X()) + (_sin_theta * record.normal.Z()),
        record.normal.Y(),
        (-_sin_theta * record.normal.X()) + (_cos_theta * record.normal.Z())
    );

    return true;
}

AxisAlignedBoundingBox ObjectYRotated::GetBoundingBox() const {
    return _bbox;
}

ObjectWithConstDensityMedium::ObjectWithConstDensityMedium(std::shared_ptr<Hittable> boundary, double density, std::shared_ptr<Texture> texture)
    : _neg_inv_density(-1/density),
      _boundary(boundary),
      _phase_function(std::make_shared<Isotropic>(texture)) {}

ObjectWithConstDensityMedium::ObjectWithConstDensityMedium(std::shared_ptr<Hittable> boundary, double density, const Color& albedo)
    : _neg_inv_density(-1/density),
      _boundary(boundary),
      _phase_function(std::make_shared<Isotropic>(albedo)) {}

bool ObjectWithConstDensityMedium::Hit(const Ray& r, Interval ray_time_interval, HitRecord& record) const {
    // -- Ray-Volume Interaction --
    // we have to be careful about the logic around the boundary to make sure this works for ray origins inside the volume
    // we assume that once a ray exits the constant medium boundary, it will continue forever outside the boundary

    HitRecord record1, record2;
    if (!_boundary->Hit(r, Interval::universe, record1)) {
        return false;
    }
    if (!_boundary->Hit(r, Interval(record1.GetHitTime()+0.0001, kInfinity), record2)) {
        return false;
    }

    if (record1.GetHitTime() < ray_time_interval.GetMin()) {
        record1.t = ray_time_interval.GetMin();
    }
    if (record2.GetHitTime() > ray_time_interval.GetMax()) {
        record2.t = ray_time_interval.GetMax();
    }
    if (record1.GetHitTime() >= record2.GetHitTime()) {
        return false;
    }
    if (record1.GetHitTime() < 0) {
        record1.t = 0;
    }

    double distance_inside_boundary = (record2.t - record1.t) * r.GetDirection().Length();
    double hit_distance = _neg_inv_density * std::log(RandomDouble());
    if (hit_distance > distance_inside_boundary) {
        return false;
    }

    record.t = record1.GetHitTime() + hit_distance / r.GetDirection().Length();
    record.hitpoint = r.AtPos(record.t);
    record.normal = Vec3(1,0,0); // no need (because of isotropic), any one is ok
    record.SetFrontFace(); // also arbitrary
    record.material = _phase_function;

    return true;
}

AxisAlignedBoundingBox ObjectWithConstDensityMedium::GetBoundingBox() const {
    return _boundary->GetBoundingBox();
}

} // namespace rabbit

} // namespace gplay
