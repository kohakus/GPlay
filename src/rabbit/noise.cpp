#include "rabbit/noise.h"

namespace gplay {

namespace rabbit {

PerlinNoise::PerlinNoise() {
    for (int i = 0; i < point_count; i++) {
        _randvec[i] = UnitVec(RandomVec3(-1,1));
    }
    GeneratePerm(_perm_x);
    GeneratePerm(_perm_y);
    GeneratePerm(_perm_z);
}

double PerlinNoise::NoiseValue(const Point3& p) const {
    double u = p.X() - std::floor(p.X());
    double v = p.Y() - std::floor(p.Y());
    double w = p.Z() - std::floor(p.Z());

    // Because of Mach bands, a known perceptual artifact of linear interpolation of color
    // use a Hermite cubic to round off the interpolation
    u = u*u*(3-2*u);
    v = v*v*(3-2*v);
    w = w*w*(3-2*w);

    int i = static_cast<int>(std::floor(p.X()));
    int j = static_cast<int>(std::floor(p.Y()));
    int k = static_cast<int>(std::floor(p.Z()));
    Vec3 c[2][2][2];
    for (int di = 0; di < 2; di++) {
        for (int dj = 0; dj < 2; dj++) {
            for (int dk = 0; dk < 2; dk++) {
                c[di][dj][dk] = _randvec[
                    _perm_x[(i+di) & (point_count-1)] ^
                    _perm_y[(j+dj) & (point_count-1)] ^
                    _perm_z[(k+dk) & (point_count-1)]
                ];
            }
        }
    }
    return PerlinInterp(c, u, v, w);
}

double PerlinNoise::NoiseTurbulence(const Point3& p, int depth) const {
    double accum = 0.0;
    double weight = 1.0;
    Point3 tmp = p;
    for (int i = 0; i < depth; i++) {
        accum += weight * NoiseValue(tmp);
        weight *= 0.5;
        tmp *= 2;
    }
    return std::fabs(accum);
}

void PerlinNoise::GeneratePerm(int perm[]) {
    for (int i = 0; i < point_count; i++) {
        perm[i] = i;
    }
    RandomPermuteArray(perm, point_count);
}

} // namespace rabbit

} // namespace gplay
