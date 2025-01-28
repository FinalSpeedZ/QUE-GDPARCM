#include "Ray.h"

// Default constructor
Ray::Ray() {}

// Parameterized constructor
Ray::Ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction) {}

// origin() method definition
const Point3& Ray::origin() const {
    return orig;
}

// direction() method definition
const Vec3& Ray::direction() const {
    return dir;
}

// at() method definition
Point3 Ray::at(double t) const {
    return orig + t * dir;
}
