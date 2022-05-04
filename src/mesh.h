#ifndef MESH_H_
#define MESH_H_

#include "hittable.h"
#include "material.h"
#include "triangle.h"
#include <memory>
#include <vector>

class Mesh : Hittable {
public:
  Mesh(int mesh_id, Material mat) : mesh_id(mesh_id), mat(mat) {}
  void add(std::shared_ptr<Triangle> t) { faces.push_back(t); }
  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &rec) const override;

  int mesh_id;
  Material mat;
  std::vector<std::shared_ptr<Triangle>> faces;
};

#endif // MESH_H_
