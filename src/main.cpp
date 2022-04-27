#include "camera.h"
#include "color.h"
#include "ray.h"
#include "vector3d.h"
#include <iostream>

color ray_color(const Ray &r) {
  vector3d unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 900;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  auto origin = point3d(0, 0, 0);
  image_plane p;
  p.nx = image_width;
  p.ny = image_height;
  p.dist = 1;
  p.l = -1;
  p.r = 1;
  p.b = -1;
  p.t = 1;

  Camera camera = Camera(origin, vector3d(0, 0, 1), vector3d(0, 1, 0), p);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      Ray r = camera.getRay(i, j);
      color pixel_color = ray_color(r);
      color_ouput(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
}
