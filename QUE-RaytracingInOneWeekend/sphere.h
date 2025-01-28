#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;

private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat;
};

#endif
