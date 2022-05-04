#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "vector3d.h"
class Material {
public:
  Material() {}
  Material(int id, vector3d ambient, vector3d diffuse, vector3d specular,
           double phong, vector3d mirror_reflectance)
      : id(id), ambient(ambient), diffuse(diffuse), specular(specular),
        phong(phong), mirror_reflectance(mirror_reflectance) {}
  int id;
  vector3d ambient;
  vector3d diffuse;
  vector3d specular;
  double phong;
  vector3d mirror_reflectance;
};
#endif // MATERIAL_H_
