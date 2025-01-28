#ifndef HIT_RECORD_H
#define HIT_RECORD_H
#include "Ray.h"
#include "Vec3.h"

class Material;

class HitRecord
{
public:
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> mat;
    double t;
    bool front_face;

    void set_face_normal(const Ray& r, const Vec3& outward_normal);
};

#endif