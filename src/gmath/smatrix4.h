#ifndef GPLAY_GMATH_SMATRIX4_H
#define GPLAY_GMATH_SMATRIX4_H
/*
The SMatrix4 class.
A tiny and simple 4D Square Matrix class.
(Using Row Major Vector by default.)
*/

#include "gmath/vec3.h"

namespace gplay {

namespace gmath {

class SMatrix4 {
public:
    SMatrix4();

    SMatrix4(double a, double b, double c, double d,
             double e, double f, double g, double h,
             double i, double j, double k, double l,
             double m, double n, double o, double p);

    SMatrix4(const SMatrix4& m);

    inline const double* operator[](int i) const { return mat[i]; }
    inline double* operator[](int i) { return mat[i]; }

    // At get the element at i-th row j-th column, both start from 0.
    inline double At(const int i, const int j) const { return mat[i][j]; }

    SMatrix4& operator*=(const SMatrix4& m2);
    SMatrix4& operator+=(const SMatrix4& m2);
    SMatrix4& operator-=(const SMatrix4& m2);

    SMatrix4& operator*=(const double t);

    // Transponse matrix transpose
    SMatrix4& Transpose();

    // Invert matrix inversion
    const SMatrix4& Invert();

    // MultPoint Point-Matrix multiplication, using Row Major Vector.
    // Points are implicitly be considered as having homogeneous coordinates. i.e. 4d vector
    void MultPoint(const Point3& src, Point3& dst) const;

    // MultDirection Direction-Matrix multiplication, using Row Major Vector.
    void MultDirection(const Vec3& src, Vec3& dst) const;

    // Inverse return inverse of a 4x4 matrix
    static SMatrix4 Inverse(const SMatrix4& m);

private:
    // Multiply naive 4x4 matrix multiplication
    static SMatrix4 Multiply(const SMatrix4& m1, const SMatrix4& m2);

public:
    double mat[4][4] = {{1,0,0,0},
                        {0,1,0,0},
                        {0,0,1,0},
                        {0,0,0,1}};
};

inline SMatrix4 operator+(const SMatrix4& m1, const SMatrix4& m2) {
    SMatrix4 res(m1);
    res += m2;
    return res;
}

inline SMatrix4 operator-(const SMatrix4& m1, const SMatrix4& m2) {
    SMatrix4 res(m1);
    res -= m2;
    return res;
}

inline SMatrix4 operator*(const SMatrix4& m1, const SMatrix4& m2) {
    SMatrix4 res(m1);
    res *= m2;
    return res;
}

inline SMatrix4 operator*(const SMatrix4& m, double t) {
    SMatrix4 res(m);
    res *= t;
    return res;
}

inline SMatrix4 operator*(double t, const SMatrix4& m) {
    return m * t;
}

SMatrix4 TransposeMatrix(const SMatrix4& m);

std::ostream& operator<<(std::ostream &os, const SMatrix4& m);

} // namespace gmath

} // namespace gplay

#endif // GPLAY_GMATH_SMATRIX4_H
