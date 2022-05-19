#include "camera.h"
#include "color.h"
#include "material.h"
#include "parse_xml.h"
#include "ray.h"
#include "triangle.h"
#include "vector3d.h"
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <fstream>
#include <future>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

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

      hit_data tmp;
      if (scene.hit(light_ray, 0.0001, std::numeric_limits<double>::infinity(),
                    tmp))
        continue;
      // Ambient
      color ambient =
          clamp(rec.material->ambient * scene.ambient_light, 0, 255);
      // Diffuse
      const auto irradiance = light.intensity / wi.length_square();
      const auto diffuse_coeff = rec.material->diffuse;
      double cosTheta = dot(unit_vector(wi), unit_vector(rec.n));
      cosTheta = (cosTheta < 0.0) ? 0.0 : cosTheta;
      auto diffuse = cosTheta * irradiance * diffuse_coeff;

      // Specular
      auto h = wi + (scene.camera.e - rec.p);
      h /= vector3d(fabs(h.x()), fabs(h.y()), fabs(h.z()));
      auto cosalpha = dot(unit_vector(rec.n), unit_vector(h));
      cosalpha = (cosalpha < 0.0) ? 0.0 : cosalpha;
      auto exp = pow(cosalpha, rec.material->phong);
      auto specular = exp * rec.material->specular * irradiance;

      // Mirror
      auto wo = unit_vector(rec.p - scene.camera.e);
      auto wr = -wo + 2 * dot(unit_vector(rec.n), wo) * unit_vector(rec.n);

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

std::vector<color> threadColor(int start, int end, Scene scene, int depth) {
  std::vector<color> result;
  const int image_width = scene.camera.plane.nx;

  for (int j = start; j < end; ++j) {
    Ray r = scene.camera.getRay(j % image_width, j / image_width);
    result.push_back(ray_color(r, scene, depth));
  }
  return result;
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "XML path is not given\n";
    return -1;
  }

  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  Parser *parser = new Parser(std::string(argv[1]));
  parser->setScene();
  std::chrono::steady_clock::time_point time_end =
      std::chrono::steady_clock::now();
  std::cout << "XML Parsing Time = "
            << std::chrono::duration_cast<std::chrono::microseconds>(time_end -
                                                                     begin)
                   .count()
            << "[ms]" << std::endl;

  Scene scene = parser->getScene();
  std::ofstream fout("output.ppm");
  const int image_width = scene.camera.plane.nx;
  const int image_height = scene.camera.plane.ny;

  const int hw_t = std::thread::hardware_concurrency();
  const int pixel_count = image_height * image_width;
  const int pixel_per_thread = pixel_count / hw_t;

  std::mutex mutex;
  std::condition_variable cvResults;
  std::vector<std::future<std::vector<color>>> m_futures;
  begin = std::chrono::steady_clock::now();
  int start = 0;
  int end = pixel_per_thread;
  for (int j = 0; j < hw_t + 1; ++j) {
    auto future = std::async(std::launch::async | std::launch::deferred,
                             threadColor, start, end, scene, scene.max_ray);

    start += pixel_per_thread;
    end += pixel_per_thread;
    if (j == hw_t) {
      auto future =
          std::async(std::launch::async | std::launch::deferred, threadColor,
                     start, pixel_count, scene, scene.max_ray);
    }
    {
      std::lock_guard<std::mutex> lock(mutex);
      m_futures.push_back(std::move(future));
    }
  }

  {
    std::unique_lock<std::mutex> lock(mutex);
    cvResults.wait(
        lock, [&m_futures, &hw_t] { return m_futures.size() == hw_t + 1; });
  }

  begin = std::chrono::steady_clock::now();
  fout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (std::future<std::vector<color>> &r : m_futures) {
    for (color color : r.get()) {
      color_ouput(fout, color);
    }
  }
  time_end = std::chrono::steady_clock::now();
  std::cout << "Rendering Time = "
            << std::chrono::duration_cast<std::chrono::microseconds>(time_end -
                                                                     begin)
                   .count()
            << "[ms]" << std::endl;
}
