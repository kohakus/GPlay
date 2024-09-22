#include "rabbit/mathtools.h"

namespace gplay {

namespace rabbit {

Interval::Interval() : _min(+kInfinity), _max(-kInfinity) {}

Interval::Interval(double min, double max) : _min(min), _max(max) {}

Interval::Interval(const Interval& a, const Interval& b) {
    // create the interval tightly enclosing the two input intervals
    _min = a._min <= b._min ? a._min : b._min;
    _max = a._max >= b._max ? a._max : b._max;
}

Point3 RandomPointInUnitDisk() {
    // rejection sampling
    while (true) {
        Point3 p = Point3(RandomDouble(-1.0,1.0), RandomDouble(-1.0,1.0), 0);
        if (p.LengthSquared() < 1.0) {
            return p;
        }
    }
}

Point3 RandomPointInDisk(double radius) {
    return radius * RandomPointInUnitDisk();
}

Point3 RandomPointInUnitSquare() {
    return Point3(RandomDouble()-0.5, RandomDouble()-0.5, 0);
}

Vec3 RandomUnitVec3() {
    // rejection sampling
    while (true) {
        Vec3 p = RandomVec3(-1.0,1.0);
        double lensq = p.LengthSquared();
        if (1e-160 < lensq && lensq <= 1.0) {
            return p / std::sqrt(lensq);
        }
    }
}

Vec3 ReflectVec3(const Vec3& v, const Vec3& n) {
    return v - 2 * Vec3Dot(v,n) * n;
}

Vec3 RefractVec3(const Vec3& uv, const Vec3& n, double eta_ratio) {
    // -- Snell's Law --
    // \eta \cdot \sin\theta = \eta' \cdot \sin\theta' =>
    // \mathbf{R'}_{\bot} = \frac{\eta}{\eta'} (\mathbf{R} + \cos\theta \mathbf{n})
    // \mathbf{R'}_{\parallel} = -\sqrt{1 - |\mathbf{R'}_{\bot}|^2} \mathbf{n}
    // \mathbf{R'} = \mathbf{R'}_{\bot} + \mathbf{R'}_{\parallel}

    double cos_theta = std::fmin(Vec3Dot(-uv, n), 1.0);
    Vec3 r_out_perp =  eta_ratio * (uv + cos_theta*n);
    Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.LengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}

double Fresnel(double cosi, double cost, double etai, double etat) {
    // The Fresnel equations describe the reflection and transmission of light
    // when incident on an interface between different optical media

    // senkrecht polarized
    double rs = (etat * cosi - etai * cost) / (etat * cosi + etai * cost);
    // parallel polarized
    double rp = (etai * cosi - etat * cost) / (etai * cosi + etat * cost);
    // use unpolarized assumption
    return (rs * rs + rp * rp) * 0.5;
}

double SchlickApprox(double cosine, double refractive_index) {
    // Schlick's approximation is a formula for approximating the contribution of the
    // Fresnel factor in the specular reflection of light from a non-conducting surface between two media
    // The specular reflection coefficient R can be approximated by:
    //  R(\theta) = R_0 + (1-R_0)(1-\cos{\theta})^5
    //  where R_0 = \bigg(\frac{\eta_1-\eta_2}{\eta_1+\eta_2}\bigg)^2

    double r0 = (1-refractive_index) / (1+refractive_index);
    r0 = r0 * r0;
    return r0 + (1-r0) * std::pow((1-cosine), 5);
}

double TrilinearInterp(double c[2][2][2], double u, double v, double w) {
    double accum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                accum += (i * u + (1 - i) * (1 - u)) *
                         (j * v + (1 - j) * (1 - v)) *
                         (k * w + (1 - k) * (1 - w)) * c[i][j][k];
            }
        }
    }
    return accum;
}

double PerlinInterp(Vec3 c[2][2][2], double u, double v, double w) {
    double accum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                Vec3 neighbor = Vec3(i, j, k);
                Vec3 weight = Vec3(u, v, w) - neighbor;
                accum += (i * u + (1 - i) * (1 - u)) *
                         (j * v + (1 - j) * (1 - v)) *
                         (k * w + (1 - k) * (1 - w)) * Vec3Dot(c[i][j][k], weight);
            }
        }
    }
    return accum;
}

} // namespace rabbit

} // namespace gplay
