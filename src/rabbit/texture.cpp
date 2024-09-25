#include "rabbit/texture.h"
#include "common/image.h"

namespace gplay {

namespace rabbit {

SolidColor::SolidColor(const Color& albedo) : _albedo(albedo) {}

SolidColor::SolidColor(double red, double green, double blue)
    : _albedo(Color(red, green, blue)) {}

Color SolidColor::Value(double u, double v, const Point3& p) const {
    return _albedo;
}

CheckerTexture::CheckerTexture(double scale_factor, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
    : _inv_scale_factor(1.0/scale_factor),
      _even(even),
      _odd(odd) {}

CheckerTexture::CheckerTexture(double scale_factor, const Color& color1, const Color& color2)
    : _inv_scale_factor(1.0/scale_factor),
      _even(std::make_shared<SolidColor>(color1)),
      _odd(std::make_shared<SolidColor>(color2)) {}

Point3 CheckerTexture::GetPositionFloor(const Point3& p, double factor) {
    return Point3(std::floor(factor * p.X()),
                  std::floor(factor * p.Y()),
                  std::floor(factor * p.Z()));
}

Color CheckerTexture::Value(double u, double v, const Point3& p) const {
    auto p_floor = GetPositionFloor(p, _inv_scale_factor);
    int x_floor = static_cast<int>(p_floor.X());
    int y_floor = static_cast<int>(p_floor.Y());
    int z_floor = static_cast<int>(p_floor.Z());

    bool is_even = (x_floor + y_floor + z_floor) % 2 == 0;
    return is_even ? _even->Value(u,v,p) : _odd->Value(u,v,p);
}

ImageTexture::ImageTexture(const std::string& filename)
    : _image(std::make_shared<gplay::Image>(filename)) {}

Color ImageTexture::Value(double u, double v, const Point3& p) const {
    if (_image->Height() <= 0) {
        // default color for debugging
        return Color(0,1,1);
    }

    int i = static_cast<int>(Interval(0,1).Clamp(u) * _image->Width());
    int j = static_cast<int>((1.0-Interval(0,1).Clamp(v)) * _image->Height());
    auto pixel = _image->GetPixelData(i, j);
    return Color(pixel[0], pixel[1], pixel[2]) * (1.0/255.0);
}

NoiseTexture::NoiseTexture(double scale_factor) : _scale_factor(scale_factor) {}

Color NoiseTexture::Value(double u, double v, const Point3& p) const {
    // Usually turbulence is used indirectly.
    // the "hello world" of procedural solid textures is a simple marble-like texture.
    // the basic idea to make color proportional to something like a sine function,
    // and use turbulence to adjust the phase which makes the stripes undulate.

    return Color(.5,.5,.5) * (1 + std::sin(_scale_factor*p.Z() + 10*_noise->NoiseTurbulence(p, 7)));
}

} // namespace rabbit

} // namespace gplay
