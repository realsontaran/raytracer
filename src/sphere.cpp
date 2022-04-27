#include "sphere.h"
bool Sphere::hit(const Ray &r, double t_min, double t_max,
                 hit_data &rec) const {
  vector3d oc = r.start() - center;
  auto a = pow(r.direction().length(), 2);
  auto half_b = dot(oc, r.direction());
  auto c = pow(oc.length(), 2) - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0)
    return false;
  auto sqrtd = sqrt(discriminant);

  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root)
      return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  rec.n = (rec.p - center) / radius;

  return true;
}
