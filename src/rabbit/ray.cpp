#include "rabbit/ray.h"

namespace gplay {

namespace rabbit {

Ray::Ray() {}

Ray::Ray(const Point3& endpoint, const Vec3& direction, double time)
    : _endpoint(endpoint), _direction(direction), _time(time) {}

Ray::Ray(const Point3& endpoint, const Vec3& direction)
    :  _endpoint(endpoint), _direction(direction), _time(0.0) {}

const Point3& Ray::GetEndpoint() const {
    return _endpoint;
}

const Vec3& Ray::GetDirection() const {
    return _direction;
}

Point3 Ray::AtPos(double time) const {
    return _endpoint + time * _direction;
}

} // namespace rabbit

} // namespace gplay
