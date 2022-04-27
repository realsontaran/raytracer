#ifndef CAMERA_H_
#define CAMERA_H_
#include "ray.h"
#include "vector3d.h"

struct image_plane {
  int nx;
  int ny;
  int l;
  int r;
  int b;
  int t;
  double dist;
};

class Camera {
public:
  Camera(point3d e, vector3d gaze, vector3d up, image_plane nearplane)
      : e(e), w(gaze), v(up), nearplane(nearplane) {
    u = cross(w, v);
  };

  Ray getRay(double u, double v) const {
    point3d m = nearplane.dist * w + e;
    point3d q =
        ((double)nearplane.l * this->u) + ((double)nearplane.t * this->v) + m;
    double su = (u + 0.5) * (nearplane.r - nearplane.l) / nearplane.nx;
    double sv = (v + 0.5) * (nearplane.t - nearplane.b) / nearplane.ny;

    vector3d s = q + su * this->u - sv * this->v;

    return Ray(e, s);
  }

private:
  point3d e;
  vector3d w;
  vector3d u;
  vector3d v;
  image_plane nearplane;
};

#endif // CAMERA_H_
