#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vector3d.h"
#include <iostream>
#include <limits>
#include <memory>

color ray_color(const Ray &r, const Hittable &world) {
  hit_data rec;
  if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec)) {
    return 0.5 * (rec.n + color(1, 1, 1));
  }
  vector3d unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 900;
  const int image_height = 900;
  auto origin = point3d(0, 0, 0);

  image_plane p;
  p.nx = image_width;
  p.ny = image_height;
  p.dist = 1;
  p.l = -1;
  p.r = 1;
  p.b = -1;
  p.t = 1;
  // World
  HittableList world;
  world.add(std::make_shared<sphere>(point3d(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point3d(0, -100.5, -1), 100));

  Camera camera = Camera(origin, vector3d(0, 0, 1), vector3d(0, 1, 0), p);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      Ray r = camera.getRay(i, j);
      color pixel_color = ray_color(r, world);
      color_ouput(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
}
