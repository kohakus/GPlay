#ifndef GPLAY_RABBIT_NOISE_H
#define GPLAY_RABBIT_NOISE_H
/*
Various noise
*/

#include "rabbit/mathtools.h"

namespace gplay {

namespace rabbit {

class Noise {
public:
    virtual ~Noise() = default;

    virtual double NoiseValue(const Point3& p) const = 0;

    // NoiseTurbulence composite noise that has multiple summed frequencies
    virtual double NoiseTurbulence(const Point3& p, int depth) const = 0;
};

class PerlinNoise : public Noise {
public:
    PerlinNoise();

    double NoiseValue(const Point3& p) const override;

    double NoiseTurbulence(const Point3& p, int depth) const override;

private:
    static void GeneratePerm(int perm[]);

public:
    static const int point_count = 256;

private:
    Vec3 _randvec[point_count];
    // Permutation for X
    int _perm_x[point_count];
    // Permutation for Y
    int _perm_y[point_count];
    // Permutation for Z
    int _perm_z[point_count];
};

} // namespace rabbit

} // namespace gplay

#endif // GPLAY_RABBIT_NOISE_H
