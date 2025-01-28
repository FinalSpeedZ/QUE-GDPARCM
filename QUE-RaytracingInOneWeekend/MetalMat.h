#ifndef METAL_MAT_H
#define METAL_MAT_H

#include "Material.h"

class MetalMat : public Material {
public:
    MetalMat(const Color& albedo, double fuzz);

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
    Color albedo;
    double fuzz;
};


#endif