#include <iomanip>
#include "gmath/smatrix4.h"

namespace gplay {

namespace gmath {

SMatrix4::SMatrix4() {}

SMatrix4::SMatrix4(double a, double b, double c, double d,
                   double e, double f, double g, double h,
                   double i, double j, double k, double l,
                   double m, double n, double o, double p) {
    mat[0][0] = a; mat[0][1] = b; mat[0][2] = c; mat[0][3] = d;
    mat[1][0] = e; mat[1][1] = f; mat[1][2] = g; mat[1][3] = h;
    mat[2][0] = i; mat[2][1] = j; mat[2][2] = k; mat[2][3] = l;
    mat[3][0] = m; mat[3][1] = n; mat[3][2] = o; mat[3][3] = p;
}

SMatrix4::SMatrix4(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d) {
    mat[0][0] = a.X();
    mat[0][1] = a.Y();
    mat[0][2] = a.Z();
    mat[0][3] = 0;

    mat[1][0] = b.X();
    mat[1][1] = b.Y();
    mat[1][2] = b.Z();
    mat[1][3] = 0;

    mat[2][0] = c.X();
    mat[2][1] = c.Y();
    mat[2][2] = c.Z();
    mat[2][3] = 0;

    mat[3][0] = d.X();
    mat[3][1] = d.Y();
    mat[3][2] = d.Z();
    mat[3][3] = 1;
}

SMatrix4::SMatrix4(const SMatrix4& m) {
    mat[0][0] = m.mat[0][0]; mat[0][1] = m.mat[0][1]; mat[0][2] = m.mat[0][2]; mat[0][3] = m.mat[0][3];
    mat[1][0] = m.mat[1][0]; mat[1][1] = m.mat[1][1]; mat[1][2] = m.mat[1][2]; mat[1][3] = m.mat[1][3];
    mat[2][0] = m.mat[2][0]; mat[2][1] = m.mat[2][1]; mat[2][2] = m.mat[2][2]; mat[2][3] = m.mat[2][3];
    mat[3][0] = m.mat[3][0]; mat[3][1] = m.mat[3][1]; mat[3][2] = m.mat[3][2]; mat[3][3] = m.mat[3][3];
}

SMatrix4& SMatrix4::operator*=(const SMatrix4& m2) {
    *this = Multiply(*this, m2);
    return *this;
}

SMatrix4& SMatrix4::operator+=(const SMatrix4& m2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] += m2.mat[i][j];
        }
    }
    return *this;
}

SMatrix4& SMatrix4::operator-=(const SMatrix4& m2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] -= m2.mat[i][j];
        }
    }
    return *this;
}

SMatrix4& SMatrix4::operator*=(const double t) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] *= t;
        }
    }
    return *this;
}

SMatrix4& SMatrix4::Transpose() {
    SMatrix4 tmp;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[i][j] = mat[j][i];
        }
    }
    *this = tmp;
    return *this;
}

const SMatrix4& SMatrix4::SMatrix4::Invert() {
  *this = Inverse(*this);
  return *this;
}

void SMatrix4::MultPoint(const Point3& src, Point3& dst) const {
    double a, b, c, w;
    a = src[0]*mat[0][0] + src[1]*mat[1][0] + src[2]*mat[2][0] + mat[3][0];
    b = src[0]*mat[0][1] + src[1]*mat[1][1] + src[2]*mat[2][1] + mat[3][1];
    c = src[0]*mat[0][2] + src[1]*mat[1][2] + src[2]*mat[2][2] + mat[3][2];
    w = src[0]*mat[0][3] + src[1]*mat[1][3] + src[2]*mat[2][3] + mat[3][3];

    dst.e[0] = a/w;
    dst.e[1] = b/w;
    dst.e[2] = c/w;
}

void SMatrix4::MultDirection(const Vec3& src, Vec3& dst) const {
    double a, b, c;
    a = src[0]*mat[0][0] + src[1]*mat[1][0] + src[2]*mat[2][0];
    b = src[0]*mat[0][1] + src[1]*mat[1][1] + src[2]*mat[2][1];
    c = src[0]*mat[0][2] + src[1]*mat[1][2] + src[2]*mat[2][2];

    dst.e[0] = a;
    dst.e[1] = b;
    dst.e[2] = c;
}

SMatrix4 SMatrix4::Inverse(const SMatrix4& m) {
    int i, j, k;
    SMatrix4 s;
    SMatrix4 t(m);

    for (i = 0; i < 3; i++) {
        int pivot = i;
        double pivotsize = t[i][i];
        if (pivotsize < 0) {
            pivotsize = -pivotsize;
        }

        for (j = i+1; j < 4; j++) {
            float tmp = t[j][i];
            if (tmp < 0) {
                tmp = -tmp;
            }
            if (tmp > pivotsize) {
                pivot = j;
                pivotsize = tmp;
            }
        }

        if (pivotsize == 0) {
            // meet singular matrix
            return SMatrix4();
        }

        if (pivot != i) {
            for (j = 0; j < 4; j++) {
                double tmp;

                tmp = t[i][j];
                t[i][j] = t[pivot][j];
                t[pivot][j] = tmp;

                tmp = s[i][j];
                s[i][j] = s[pivot][j];
                s[pivot][j] = tmp;
            }
        }

        for (j = i+1; j < 4; j++) {
            double f = t[j][i] / t[i][i];
            for (k = 0; k < 4; k++) {
                t[j][k] -= f * t[i][k];
                s[j][k] -= f * s[i][k];
            }
        }
    }

    // Backward substitution
    for (i = 3; i >= 0; --i) {
        double f;
        if ((f = t[i][i]) == 0) {
            // singular matrix
            return SMatrix4();
        }

        for (j = 0; j < 4; j++) {
            t[i][j] /= f;
            s[i][j] /= f;
        }

        for (j = 0; j < i; j++) {
            f = t[j][i];
            for (k = 0; k < 4; k++) {
                t[j][k] -= f * t[i][k];
                s[j][k] -= f * s[i][k];
            }
        }
    }
    return s;
}

SMatrix4 SMatrix4::Multiply(const SMatrix4& m1, const SMatrix4& m2) {
    SMatrix4 res;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = m1[i][0]*m2[0][j] + m1[i][1]*m2[1][j] +
                        m1[i][2]*m2[2][j] + m1[i][3]*m2[3][j];
        }
    }
    return res;
}

SMatrix4 TransposeMatrix(const SMatrix4& m) {
    SMatrix4 res(m);
    res.Transpose();
    return res;
}

std::ostream& operator<<(std::ostream &os, const SMatrix4& m) {
    std::ios_base::fmtflags oldFlags = os.flags();
    int width = 12; // total with of the displayed number
    os.precision(5); // control the number of displayed decimals
    os.setf(std::ios_base::fixed);

    os << "[" << std::setw(width) << m[0][0] <<
          " " << std::setw(width) << m[0][1] <<
          " " << std::setw(width) << m[0][2] <<
          " " << std::setw(width) << m[0][3] << "\n" <<
          " " << std::setw(width) << m[1][0] <<
          " " << std::setw(width) << m[1][1] <<
          " " << std::setw(width) << m[1][2] <<
          " " << std::setw(width) << m[1][3] << "\n" <<
          " " << std::setw(width) << m[2][0] <<
          " " << std::setw(width) << m[2][1] <<
          " " << std::setw(width) << m[2][2] <<
          " " << std::setw(width) << m[2][3] << "\n" <<
          " " << std::setw(width) << m[3][0] <<
          " " << std::setw(width) << m[3][1] <<
          " " << std::setw(width) << m[3][2] <<
          " " << std::setw(width) << m[3][3] << "]";

    os.flags(oldFlags);
    return os;
}

} // namespace gmath

} // namespace gplay
