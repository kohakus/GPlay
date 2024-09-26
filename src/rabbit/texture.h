#ifndef GPLAY_RABBIT_TEXTURE_H
#define GPLAY_RABBIT_TEXTURE_H
/*
Class Texture
*/

#include "rabbit/mathtools.h"
#include "rabbit/noise.h"

namespace gplay {

class Image;

namespace rabbit {


class Texture {
public:
    virtual ~Texture() = default;

    virtual Color Value(double u, double v, const Point3& p) const = 0;
};

// SolidColor constant color texture
class SolidColor : public Texture {
public:
    SolidColor(const Color& albedo);

    SolidColor(double red, double green, double blue);

    Color Value(double u, double v, const Point3& p) const override;

private:
    Color _albedo;
};

// CheckerTexture 3D checker pattern
class CheckerTexture : public Texture {
public:
    CheckerTexture(double scale_factor, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);

    CheckerTexture(double scale_factor, const Color& color1, const Color& color2);

    Color Value(double u, double v, const Point3& p) const override;

private:
    // GetPositionFloor ...
    static Point3 GetPositionFloor(const Point3& p, double factor);

private:
    // Control the size of the checker pattern
    double _inv_scale_factor;
    // Can be a constant texture or some other procedural texture
    std::shared_ptr<Texture> _even;
    // Can be a constant texture or some other procedural texture
    std::shared_ptr<Texture> _odd;
};

// ImageTexture ...
class ImageTexture : public Texture {
public:
    ImageTexture(const std::string& filename);

    Color Value(double u, double v, const Point3& p) const override;

private:
    std::shared_ptr<gplay::Image> _image;
};

// NoiseTexture ...
class NoiseTexture : public Texture {
public:
    NoiseTexture(double scale_factor, std::shared_ptr<Noise> noise);

    Color Value(double u, double v, const Point3& p) const override;

private:
    double _scale_factor;
    std::shared_ptr<Noise> _noise;
};

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_TEXTURE_H
