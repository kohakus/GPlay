#ifndef GPLAY_RABBIT_MATERIAL_H
#define GPLAY_RABBIT_MATERIAL_H
/*
Various materials
reference: https://github.com/RayTracing/raytracing.github.io/blob/release/src/TheNextWeek
*/

#include "rabbit/hittable.h"
#include "rabbit/texture.h"

namespace gplay {

namespace rabbit {

class Material {
public:
    virtual ~Material() = default;

    virtual Color Emitted(double u, double v, const Point3& p) const {
        return Color(0, 0, 0);
    }

    virtual bool Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const {
        return false;
    }
};

// Lambertian diffuse reflectance
class Lambertian : public Material {
public:
    Lambertian(const Color& albedo);
    Lambertian(std::shared_ptr<Texture> texture);

    bool Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const override;

private:
    std::shared_ptr<Texture> _texture;
};

// Metal mirrored light reflection
class Metal : public Material {
public:
    Metal(const Color& albedo, double fuzz);

    bool Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const override;

private:
    // Define some form of fractional reflectance i.e. whiteness
    // Albedo will vary with material color and can also vary with incident viewing direction
    Color _albedo;
    // Fuzziness parameter i.e. the radius of the fuzz sphere
    double _fuzz;
};

// Dielectric reflection and refraction
class Dielectric : public Material {
public:
    Dielectric(double refractive_index);

    bool Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const override;

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double _refractive_index;
};

// DiffuseLight a light emitting material
class DiffuseLight : public Material {
public:
    DiffuseLight(const Color& emit);
    DiffuseLight(std::shared_ptr<Texture> texture);

    Color Emitted(double u, double v, const Point3& p) const override;

private:
    std::shared_ptr<Texture> _texture;
};

// Isotropic volumes or participating media
class Isotropic : public Material {
public:
    Isotropic(const Color& albedo);
    Isotropic(std::shared_ptr<Texture> texture);

    bool Scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& r_scattered) const override;

private:
    std::shared_ptr<Texture> _texture;
};


} // namespace rabbit

} // namespace gplay


#endif // GPLAY_RABBIT_MATERIAL_H
