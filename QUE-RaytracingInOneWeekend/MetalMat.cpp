#include "MetalMat.h"

MetalMat::MetalMat(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

bool MetalMat::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());

    scattered = Ray(rec.p, reflected);
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
}