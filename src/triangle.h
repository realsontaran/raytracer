#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "hittable.h"
#include "vector3d.h"
#include <limits>

class Triangle : public Hittable {
public:
  Triangle() {}
  Triangle(point3d a, point3d b, point3d c) : v1(a), v2(b), v3(c) {}

  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &rec) const override;

private:
  point3d v1, v2, v3;
};

inline bool Triangle::hit(const Ray &r, double t_min, double t_max,
                          hit_data &rec) const {
  double tolerance = 0.0001;

  vector3d head = r.direction();
  vector3d tail = r.start();

  vector3d e1 = v2 - v1;
  vector3d e2 = v3 - v1;

  vector3d h = cross(head, e2);
  double a = dot(e1, h);

  if (a > -tolerance && a < tolerance) {
    return false;
  }

  double f = 1.0 / a;
  vector3d s = tail - v1;
  double u = f * dot(s, h);

  if (u < 0.0 || u > 1.0) {
    return false;
  }

  vector3d q = cross(s, e1);
  float v = f * dot(head, q);

  if (v < 0.0 || u + v > 1.0) {
    return false;
  }

  double t = f * dot(e2, q);

  if (t_min < t && t < t_max) {
    rec.t = t;
    rec.p = r.at(rec.t);
    vector3d outward_normal = unit_vector(cross(e1, e2));
    // rec.set_face_normal(r, outward_normal);
    rec.n = outward_normal;
    return true;
  }
  return false;
}
#endif // TRIANGLE_H_
