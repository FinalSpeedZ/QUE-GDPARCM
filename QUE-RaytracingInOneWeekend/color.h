#ifndef COLOR_H
#define COLOR_H

#include "Interval.h"
#include "Vec3.h"

using Color = Vec3;

inline double linear_to_gamma(double linear_component); 

Vec3 write_color(const Color& pixel_color); 

#endif