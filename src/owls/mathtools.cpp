#include "owls/mathtools.h"

namespace gplay {

namespace owls {

gmath::Vec2 DeriveVec2FromVec3(const gmath::Vec3& v) {
    return gmath::Vec2(v.X(), v.Y());
}

} // namespace owls

} // namespace gplay
