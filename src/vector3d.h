#ifndef VECTOR3D_H_
#define VECTOR3D_H_
#include <algorithm>
#include <cmath>
#include <iostream>

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
  double length_square() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  vector3d operator-() const { return vector3d(-e[0], -e[1], -e[2]); }

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
  vector3d &operator/=(const vector3d &other) {
    this->e[0] /= other.x();
    this->e[1] /= other.y();
    this->e[2] /= other.z();
    return *this;
  }

private:
  double e[3];
};

using point3d = vector3d;
using color = vector3d;

inline vector3d operator+(const vector3d &u, const vector3d &v) {
  return vector3d(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vector3d operator-(const vector3d &u, const vector3d &v) {
  return vector3d(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vector3d operator*(const vector3d &u, const vector3d &v) {
  return vector3d(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vector3d operator*(double t, const vector3d &v) {
  return vector3d(t * v.x(), t * v.y(), t * v.z());
}

inline vector3d operator/(vector3d v, double t) { return (1 / t) * v; }

inline double dot(const vector3d &u, const vector3d &v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline vector3d cross(const vector3d &u, const vector3d &v) {
  return vector3d(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(),
                  u.x() * v.y() - u.y() * v.x());
}

inline vector3d unit_vector(vector3d v) { return v / v.length(); }

inline vector3d clamp(vector3d v, double lo, double hi) {
  double x, y, z;
  x = v.x() < lo ? lo : v.x() > hi ? hi : v.x();
  y = v.y() < lo ? lo : v.y() > hi ? hi : v.y();
  z = v.z() < lo ? lo : v.z() > hi ? hi : v.z();
  return vector3d(x, y, z);
}
inline std::ostream &operator<<(std::ostream &outstream, const vector3d &v) {
  return outstream << v.x() << ' ' << v.y() << ' ' << v.z() << '\n';
}

#endif // VECTOR3D_H_
