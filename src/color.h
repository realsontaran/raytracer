#ifndef COLOR_H_
#define COLOR_H_
#include "vector3d.h"
#include <iostream>

void color_ouput(std::ostream &out, color pixel_color);
color cast0_255(color pixel_color);
#endif // COLOR_H_
