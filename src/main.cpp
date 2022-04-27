#include "color.h"
#include "vector3d.h"

#include <iostream>

int main() {

  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      color pixel_color(double(i) / (image_width - 1),
                        double(j) / (image_height - 1), 0.25);
      color_ouput(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
}