#include "color.h"
#include "vector3d.h"
void color_ouput(std::ostream &out, color pixel_color) {
  out << (int)pixel_color.x() << ' ' << (int)pixel_color.y() << ' '
      << (int)pixel_color.z() << '\n';
}

color cast0_255(color pixel_color) {
  return color(static_cast<int>(255.999 * pixel_color.x()),
               static_cast<int>(255.999 * pixel_color.y()),
               static_cast<int>(255.999 * pixel_color.z()));
}
