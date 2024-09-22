#ifndef GPLAY_RABBIT_TEXTURE_H
#define GPLAY_RABBIT_TEXTURE_H
/*
Class Texture
*/

#include "rabbit/mathtools.h"

namespace gplay {

namespace rabbit {

class Texture {
public:
    virtual ~Texture() = default;

    virtual Color Value(double u, double v, const Point3& p) const = 0;
};

class SolidColor : public Texture {
public:
    SolidColor(const Color& albedo);

    SolidColor(double red, double green, double blue);

    Color Value(double u, double v, const Point3& p) const override;

private:
    Color _albedo;
};

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_TEXTURE_H
