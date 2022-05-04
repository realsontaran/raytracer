#ifndef SCENE_H_
#define SCENE_H_

#include "camera.h"
#include "light.h"
#include "material.h"
#include "mesh.h"
#include "vector3d.h"
#include <memory>
#include <vector>

class Scene : Hittable {
public:
  Scene() {}
  void insertVertex(point3d t) { vertex_data.push_back(t); }
  void insertMaterial(Material m) { material_list.push_back(m); }
  void insertPointLight(PointLightSource p) { point_lights.push_back(p); }
  void setCamera(Camera cam) { camera = cam; }
  void setBG(color bg) { bg_color = bg; }
  void setAmbient(color ambient) { ambient_light = ambient; }
  void setRayDepth(int d) { max_ray = d; }
  virtual bool hit(const Ray &r, double t_min, double t_max,
                   hit_data &rec) const override;

  Camera camera;
  color bg_color;
  color ambient_light;
  int max_ray;
  std::vector<PointLightSource> point_lights;
  std::vector<std::shared_ptr<Mesh>> objects;
  std::vector<Material> material_list;
  std::vector<point3d> vertex_data;
};
#endif // SCENE_H_
