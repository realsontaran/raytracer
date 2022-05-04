#include "mesh.h"
#include "material.h"
#include <memory>
bool Mesh::hit(const Ray &r, double t_min, double t_max, hit_data &rec) const {
  hit_data temp_rec;
  bool hit_anything = false;
  auto closest_so_far = t_max;

  for (const auto &face : faces) {
    if (face->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
      rec.material = std::make_shared<Material>(mat);
    }
  }

  return hit_anything;
}
