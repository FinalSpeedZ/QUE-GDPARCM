#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <random>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
extern const double infinity;
extern const double pi;

// Utility Functions
double degrees_to_radians(double degrees);
double random_double();
double random_double(double min, double max);

// Common Headers
#include "Color.h"
#include "Interval.h"
#include "Ray.h"
#include "Vec3.h"
#include "ImageSaver.h"

#endif
