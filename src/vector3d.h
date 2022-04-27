#ifndef VECTOR3D_H_
#define VECTOR3D_H_
#include <cmath>

class vector3d {
public:
  vector3d() : e{0, 0, 0} {};
  vector3d(double x, double y, double z) : e{x, y, z} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }
  double length() const {
    return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
  }

  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  vector3d operator-() { return vector3d(-e[0], -e[1], -e[2]); }

  vector3d &operator+=(vector3d &other) {
    this->e[0] += other.e[0];
    this->e[1] += other.e[1];
    this->e[2] += other.e[2];
    return *this;
  }

  vector3d &operator*=(const double t) {
    this->e[0] *= t;
    this->e[1] *= t;
    this->e[2] *= t;
    return *this;
  }

  vector3d &operator/=(const double t) {
    this->e[0] /= t;
    this->e[1] /= t;
    this->e[2] /= t;
    return *this;
  }

private:
  double e[3];
};

using point3d = vector3d;
using color = vector3d;

#endif // VECTOR3D_H_
