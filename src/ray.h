#ifndef RAY_H_
#define RAY_H_
#include "vector3d.h"

class Ray {
public:
  Ray() {}
  Ray(const point3d &start, const vector3d &direction)
      : s(start), d(direction) {}

  point3d start() const { return s; }
  vector3d direction() const { return d; }
  point3d at(double t) const { return s + t * d; }

private:
  point3d s;
  vector3d d;
};
#endif // RAY_H_
