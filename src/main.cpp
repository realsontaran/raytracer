#include "camera.h"
#include "color.h"
#include "material.h"
#include "parse_xml.h"
#include "ray.h"
#include "triangle.h"
#include "vector3d.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

using std::fabs;
using std::pow;

color ray_color(const Ray &r, Scene scene) {
  hit_data rec;
  if (scene.hit(r, 0, std::numeric_limits<double>::infinity(), rec)) {
    for (const auto light : scene.point_lights) {
      Ray light_ray = Ray(r.start(), r.start() - light.position);
      hit_data tmp;
      color ambient =
          clamp(rec.material->ambient * scene.ambient_light, 0, 255);

      if (scene.hit(light_ray, 0, std::numeric_limits<double>::infinity(),
                    tmp)) {
        return ambient;
      } else {
        const auto irradiance =
            light.intensity / (r.start() - light.position).length_square();
        const auto diffuse_coeff = rec.material->diffuse;
        double cosTheta =
            dot(unit_vector(light_ray.direction()), unit_vector(rec.n));
        cosTheta = (cosTheta < 0.0) ? 0.0 : cosTheta;
        auto diffuse = cosTheta * irradiance * diffuse_coeff;

        auto h = light_ray.direction() + (rec.p - scene.camera.e);
        h /= vector3d(fabs(h.x()), fabs(h.y()), fabs(h.z()));
        auto cosalpha = dot(unit_vector(rec.n), unit_vector(h));
        cosalpha = (cosalpha < 0.0) ? 0.0 : cosalpha;
        auto exp = pow(cosalpha, rec.material->phong);
        auto specular = exp * rec.material->specular * irradiance;

        return clamp(diffuse + ambient, 0, 255);
      }
    }
  }
  return scene.bg_color;
}

int main() {
  Parser *parser = new Parser(std::string("scene.xml"));
  parser->setScene();
  Scene scene = parser->getScene();
  Camera camera = parser->getScene().camera;
  std::ofstream fout("output.ppm");

  const int image_width = camera.plane.nx;
  const int image_height = camera.plane.ny;
  fout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; ++j) {
    for (int i = 0; i < image_width; ++i) {
      Ray r = camera.getRay(i, j);
      color pixel_color = ray_color(r, scene);
      color_ouput(fout, pixel_color);
    }
  }
}
