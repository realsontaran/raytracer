#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "material.h"
#include "ray.h"
#include "vector3d.h"
#include <memory>

struct hit_data {
  point3d p;
  vector3d n;
  double t;
  std::shared_ptr<Material> material;
};

class Hittable {
public:
  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &data) const = 0;
};

#endif // HITTABLE_H_
