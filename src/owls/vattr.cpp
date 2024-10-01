#include "owls/vattr.h"

namespace gplay {

namespace owls {

VertexVec3Attribute::VertexVec3Attribute() {}

VertexVec3Attribute::VertexVec3Attribute(double a, double b, double c)
    : _vec{a,b,c} {}

VertexVec3Attribute::VertexVec3Attribute(const gmath::Vec3& vec)
    : _vec(vec) {}

int VertexVec3Attribute::GetDimNum() const {
    return 3;
}

const gmath::Vec3& VertexVec3Attribute::GetVec3Rep() const {
    return _vec;
}

VertexVec2Attribute VertexVec3Attribute::DeriveVec2Attribute() const {
    return VertexVec2Attribute(_vec.X(), _vec.Y());
}

VertexVec2Attribute::VertexVec2Attribute() {}

VertexVec2Attribute::VertexVec2Attribute(double a, double b)
    : _vec{a,b} {}

VertexVec2Attribute::VertexVec2Attribute(const gmath::Vec2& vec)
    : _vec(vec) {}

int VertexVec2Attribute::GetDimNum() const {
    return 2;
}

const gmath::Vec2& VertexVec2Attribute::GetVec2Rep() const {
    return _vec;
}

VertexVec3Attribute VertexVec2Attribute::DeriveVec3Attribute() const {
    return VertexVec3Attribute(_vec.X(), _vec.Y(), 1);
}

} // namespace owls

} // namespace gplay
