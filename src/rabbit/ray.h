#ifndef GPLAY_RABBIT_RAY_H
#define GPLAY_RABBIT_RAY_H
/*
Class Ray
*/

#include "rabbit/vec3.h"

namespace gplay {

namespace rabbit {

class Ray {
public:
    Ray();
    Ray(const Point3& endpoint, const Vec3& direction, double time);
    Ray(const Point3& endpoint, const Vec3& direction);

    const Point3& GetEndpoint() const;

    const Vec3& GetDirection() const;

    Point3 AtPos(double time) const;

    inline double GetTime() const { return _time; }

private:
    Point3 _endpoint;
    Vec3 _direction;
    double _time;
};

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_RAY_H
