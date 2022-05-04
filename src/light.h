#ifndef LIGHT_H_
#define LIGHT_H_
#include "vector3d.h"
class PointLightSource {
public:
  PointLightSource(int id, point3d pos, vector3d inten)
      : id(id), position(pos), intensity(inten) {}

  int id;
  point3d position;
  vector3d intensity;
};

#endif // LIGHT_H_
