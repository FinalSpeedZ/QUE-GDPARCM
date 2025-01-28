#ifndef VEC_3_H
#define VEC_3_H

#include <iostream>
#include <cmath> // For math functions like sqrt, fabs, etc.

class Vec3 {
public:
    double e[3];

    Vec3();
    Vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3& v);
    Vec3& operator*=(double t);
    Vec3& operator/=(double t);

    double length() const;
    double length_squared() const;
    bool near_zero() const;

    static Vec3 random();
    static Vec3 random(double min, double max);
};

using Point3 = Vec3; // Alias for Vec3

// Vector Utility Functions
std::ostream& operator<<(std::ostream& out, const Vec3& v);
Vec3 operator+(const Vec3& u, const Vec3& v);
Vec3 operator-(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, const Vec3& v);
Vec3 operator*(double t, const Vec3& v);
Vec3 operator*(const Vec3& v, double t);
Vec3 operator/(const Vec3& v, double t);

double dot(const Vec3& u, const Vec3& v);
Vec3 cross(const Vec3& u, const Vec3& v);
Vec3 unit_vector(const Vec3& v);
Vec3 random_unit_vector();
Vec3 random_on_hemisphere(const Vec3& normal);
Vec3 reflect(const Vec3& v, const Vec3& n);
Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat);
Vec3 random_in_unit_disk();

#endif
