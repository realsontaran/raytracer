#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vector3d.h"
#include <cmath>
class sphere : public Hittable {
public:
  sphere() {}
  sphere(point3d cen, double r) : center(cen), radius(r){};

  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &rec) const override;

public:
  point3d center;
  double radius;
};

inline bool sphere::hit(const Ray &r, double t_min, double t_max,
                        hit_data &rec) const {
  vector3d oc = r.start() - center;
  auto a = pow(r.direction().length(), 2);
  auto half_b = dot(oc, r.direction());
  auto c = pow(oc.length(), 2) - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return false;
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vector3d outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);

  return true;
}

#endif
