#ifndef LAMBERTIAN_MAT_H
#define LAMBERTIAN_MAT_H

#include "Material.h"

class LambertianMat : public Material
{
public:
    LambertianMat(const Color& albedo);

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
    Color albedo;
};

#endif