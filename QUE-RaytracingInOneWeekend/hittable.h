#ifndef HITTABLE_H
#define HITTABLE_H

#include "HitRecord.h"

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

#endif
