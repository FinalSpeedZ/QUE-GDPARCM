#ifndef DIELECTRIC_MAT_H
#define DIELECTRIC_MAT_H

#include "Material.h"

class DielectricMat : public Material
{
public:
    DielectricMat(double refraction_index);

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
    static double reflectance(double cosine, double refraction_index);

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;
};

#endif