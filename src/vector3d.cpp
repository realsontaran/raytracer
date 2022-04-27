#include "vector3d.h"
#include <iostream>

vector3d operator+(const vector3d &u, const vector3d &v) {
  return vector3d(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

vector3d operator-(const vector3d &u, const vector3d &v) {
  return vector3d(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

vector3d operator*(const vector3d &u, const vector3d &v) {
  return vector3d(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

vector3d operator*(double t, const vector3d &v) {
  return vector3d(t * v.x(), t * v.y(), t * v.z());
}

vector3d operator/(vector3d v, double t) { return (1 / t) * v; }

double dot(const vector3d &u, const vector3d &v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

vector3d cross(const vector3d &u, const vector3d &v) {
  return vector3d(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(),
                  u.x() * v.y() - u.y() * v.x());
}

vector3d unit_vector(vector3d v) { return v / v.length(); }

std::ostream &operator<<(std::ostream &outstream, const vector3d &v) {
  return outstream << v.x() << ' ' << v.y() << ' ' << v.z() << '\n';
}
