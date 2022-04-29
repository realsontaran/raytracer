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
  Camera(point3d e, vector3d gaze, vector3d up, image_plane plane)
      : e(e), w(-gaze), v(-up), plane(plane) {
    u = cross(v, w);
  };

  Ray getRay(double i, double j) const {
    point3d m = e + (plane.dist * w);
    point3d q = ((double)plane.l * u) + ((double)plane.t * v) + m;

    double su = (i + 0.5) * (plane.r - plane.l) / (plane.nx - 1);
    double sv = (j + 0.5) * (plane.t - plane.b) / (plane.ny - 1);

    vector3d s = q + (su * u) - (sv * v);

    return Ray(e, s - e);
  }

private:
  point3d e;
  vector3d w;
  vector3d u;
  vector3d v;
  image_plane plane;
};

#endif // CAMERA_H_
