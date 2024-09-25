#include "rabbit/material.h"

namespace gplay {

namespace rabbit {

Lambertian::Lambertian(const Color& albedo) : _texture(std::make_shared<SolidColor>(albedo)) {}

Lambertian::Lambertian(std::shared_ptr<Texture> texture) : _texture(texture) {}

bool Lambertian::Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const {
    Vec3 scatter_direction = record.normal + RandomUnitVec3();
    if (scatter_direction.IsNearZero()) {
        scatter_direction = record.normal;
    }

    r_scattered = Ray(record.hitpoint, scatter_direction, r_in.GetTime());
    attenuation = _texture->Value(record.u, record.v, record.hitpoint);
    return true;
}

Metal::Metal(const Color& albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz < 1 ? fuzz : 1) {}

bool Metal::Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const {
    Vec3 reflected = ReflectVec3(r_in.GetDirection(), record.normal);
    reflected = UnitVec(reflected) + (_fuzz * RandomUnitVec3());
    r_scattered = Ray(record.hitpoint, reflected, r_in.GetTime());
    attenuation = _albedo;
    return Vec3Dot(r_scattered.GetDirection(), record.normal) > 0;
}

Dielectric::Dielectric(double refractive_index) : _refractive_index(refractive_index) {}

bool Dielectric::Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const {
    attenuation = Color(1.0, 1.0, 1.0); // the glass surface absorbs nothing
    double ri = record.IsFrontFace() ? (1.0/_refractive_index) : _refractive_index;
    Vec3 unit_direction = UnitVec(r_in.GetDirection());
    double cos_theta = std::fmin(Vec3Dot(-unit_direction, record.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    Vec3 scatter_direction;
    if (ri*sin_theta > 1.0 || SchlickApprox(cos_theta, ri) > RandomDouble()) {
        scatter_direction = ReflectVec3(unit_direction, record.normal);
    } else {
        scatter_direction = RefractVec3(unit_direction, record.normal, ri);
    }
    r_scattered = Ray(record.hitpoint, scatter_direction, r_in.GetTime());
    return true;
}

DiffuseLight::DiffuseLight(const Color& emit) : _texture(std::make_shared<SolidColor>(emit)) {}

DiffuseLight::DiffuseLight(std::shared_ptr<Texture> texture) : _texture(texture) {}

Color DiffuseLight::Emitted(double u, double v, const Point3& p) const {
    return _texture->Value(u, v, p);
}

Isotropic::Isotropic(const Color& albedo) : _texture(std::make_shared<SolidColor>(albedo)) {}

Isotropic::Isotropic(std::shared_ptr<Texture> texture) : _texture(texture) {}

bool Isotropic::Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const {
    r_scattered = Ray(record.hitpoint, RandomUnitVec3(), r_in.GetTime()); // isotropic scatter
    attenuation = _texture->Value(record.u, record.v, record.hitpoint);
    return true;
}

} // namespace rabbit

} // namespace gplay
