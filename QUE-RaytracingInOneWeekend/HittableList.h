#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <vector>

class HittableList : public Hittable 
{
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object);

    void clear();

    void add(std::shared_ptr<Hittable> object);
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};

#endif