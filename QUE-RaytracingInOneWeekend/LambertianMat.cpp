#include "LambertianMat.h"

LambertianMat::LambertianMat(const Color& albedo) : albedo(albedo) {}

bool LambertianMat::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const 
{
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}