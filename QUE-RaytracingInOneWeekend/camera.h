#ifndef CAMERA_H
#define CAMERA_H

#include "Hittable.h"
#include "Material.h"
#include "ImageSaver.h"
#include <iostream>

class Camera {
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width = 100;  // Rendered image width in pixel count
    int    samples_per_pixel = 10;   // Count of random samples for each pixel
    int    max_depth = 10;   // Maximum number of ray bounces into scene

    double vfov = 90;  // Vertical view angle (field of view)
    Point3 lookfrom = Point3(0, 0, 0);   // Point camera is looking from
    Point3 lookat = Point3(0, 0, -1);  // Point camera is looking at
    Vec3   vup = Vec3(0, 1, 0);     // Camera-relative "up" direction

    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    void initialize();

    //void render(const Hittable& world);

private:
    int    image_height;   // Rendered image height
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    Point3 center;         // Camera center
    Point3 pixel00_loc;    // Location of pixel 0, 0
    Vec3   pixel_delta_u;  // Offset to pixel to the right
    Vec3   pixel_delta_v;  // Offset to pixel below
    Vec3   u, v, w;        // Camera frame basis vectors
    Vec3   defocus_disk_u; // Defocus disk horizontal radius
    Vec3   defocus_disk_v; // Defocus disk vertical radius

    Vec3 sample_square() const;
    Point3 defocus_disk_sample() const;

public:
    Ray get_ray(int i, int j) const;
    Color ray_color(const Ray& r, int depth, const Hittable& world) const;
};

#endif
