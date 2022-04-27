#ifndef SPHERE_H_
#define SPHERE_H_

#include "hittable.h"
#include "vector3d.h"

class Sphere : Hittable {
public:
  Sphere() {}
  Sphere(point3d c, double r) : center(c), radius(r){};
  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &data) const override;

private:
  point3d center;
  double radius;
};

#endif // SPHERE_H_
