#ifndef GPLAY_OWLS_VATTR_H
#define GPLAY_OWLS_VATTR_H
/*
Class VertexAttribute
*/

#include "owls/mathtools.h"

namespace gplay {

namespace owls {

class VertexAttribute {
public:
    virtual ~VertexAttribute() = default;

    virtual int GetDimNum() const = 0;
};

class VertexVec2Attribute;

class VertexVec3Attribute : public VertexAttribute {
public:
    VertexVec3Attribute();

    VertexVec3Attribute(double a, double b, double c);

    VertexVec3Attribute(const gmath::Vec3& vec);

    int GetDimNum() const override;

    const gmath::Vec3& GetVec3Rep() const;

    VertexVec2Attribute DeriveVec2Attribute() const;

private:
    gmath::Vec3 _vec;
};

class VertexVec2Attribute : public VertexAttribute {
public:
    VertexVec2Attribute();

    VertexVec2Attribute(double a, double b);

    VertexVec2Attribute(const gmath::Vec2& vec);

    int GetDimNum() const override;

    const gmath::Vec2& GetVec2Rep() const;

    VertexVec3Attribute DeriveVec3Attribute() const;

private:
    gmath::Vec2 _vec;
};

// VertexRGBColorAttribute attribute of RGB color
using VertexRGBColorAttribute = VertexVec3Attribute;

// VertexUVAttribute attribute of texture coordinates
using VertexUVAttribute = VertexVec2Attribute;

} // namespace owls

} // namespace gplay

#endif // GPLAY_OWLS_VATTR_H
