#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "hittable.h"
#include "vector3d.h"

class Triangle : public Hittable {
public:
  Triangle() {}
  Triangle(point3d a, point3d b, point3d c) : a(a), b(b), c(c) {}

  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &rec) const override;

private:
  point3d a, b, c;
};

inline bool Triangle::hit(const Ray &r, double t_min, double t_max,
                          hit_data &rec) const {
  const double EPSILON = 0.0000001;

  vector3d e1, e2, h, s, q;
  double a1, f, u, v;

  e1 = b - a;
  e2 = c - a;

  h = cross(r.direction(), e2);
  a1 = dot(e1, h);

  if (a1 > -EPSILON && a1 < EPSILON)
    return false;

  f = 1.0 / a1;

  s = r.start() - a;
  u = f * dot(s, h);

  if (u < 0.0 || u > 1.0)
    return false;

  q = cross(s, e1);
  v = f * dot(r.direction(), q);

  if (v < 0.0 || u + v > 1.0)
    return false;

  double t = f * dot(e2, q);

  if (t_min < t && t < t_max) // ray intersection
  {
    rec.t = t;
    rec.p = r.at(t);
    rec.n = unit_vector(cross(e1, e2));
    return true;
  }

  return false;
}
#endif // TRIANGLE_H_
