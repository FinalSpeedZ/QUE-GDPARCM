#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray
{
public:
    Ray(); // Default constructor declaration
    Ray(const Point3& origin, const Vec3& direction); // Parameterized constructor declaration

    const Point3& origin() const; // origin() method declaration
    const Vec3& direction() const; // direction() method declaration
    Point3 at(double t) const; // at() method declaration

private:
    Point3 orig;
    Vec3 dir;
};

#endif
