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

color ray_color(const Ray &r, Scene scene, int depth) {
  hit_data rec;
  if (depth <= 0)
    return color(0, 0, 0);

  if (scene.hit(r, 0.0001, std::numeric_limits<double>::infinity(), rec)) {
    for (const auto light : scene.point_lights) {
      Ray light_ray = Ray(rec.p, light.position - rec.p);
      vector3d wi = (light.position - rec.p);
      color ambient =
          clamp(rec.material->ambient * scene.ambient_light, 0, 255);

      hit_data tmp;
      if (scene.hit(light_ray, 0.0001, std::numeric_limits<double>::infinity(),
                    tmp))
        continue;

      const auto irradiance = light.intensity / wi.length_square();

      const auto diffuse_coeff = rec.material->diffuse;

      double cosTheta = dot(unit_vector(wi), unit_vector(rec.n));
      cosTheta = (cosTheta < 0.0) ? 0.0 : cosTheta;

      auto diffuse = cosTheta * irradiance * diffuse_coeff;

      auto h = wi + (scene.camera.e - rec.p);
      h /= vector3d(fabs(h.x()), fabs(h.y()), fabs(h.z()));
      auto cosalpha = dot(unit_vector(rec.n), unit_vector(h));
      cosalpha = (cosalpha < 0.0) ? 0.0 : cosalpha;
      auto exp = pow(cosalpha, rec.material->phong);
      auto specular = exp * rec.material->specular * irradiance;

      auto result = diffuse;
      result += ambient;
      result += specular;

      const auto target = rec.p + rec.n;

      result = result + ray_color(Ray(rec.p, target - rec.p), scene, depth - 1);
      return clamp(result, 0, 255);
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
      color pixel_color = ray_color(r, scene, scene.max_ray);
      color_ouput(fout, pixel_color);
    }
  }
}
