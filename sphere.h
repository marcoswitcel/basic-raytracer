#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "geometry.h"
#include <cmath>
#include <limits>

struct Material
{
    Material(const Vec3f &color) : diffuse_color(color) {}
    Material() : diffuse_color() {}
    Vec3f diffuse_color;
};

struct Light
{
    Light(const Vec3f &p, const float &i) : position(p), intensity(i) {}
    Vec3f position;
    float intensity;
};

struct Sphere
{
    Vec3f center;
    float radius;
    Material material;

    Sphere(const Vec3f &c, const float &r, const Material &m) : center(c), radius(r), material(m) {}

    bool ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const
    {
        Vec3f L = center - orig;
        float tca = L * dir;
        float d2 = L * L - tca * tca;
        if (d2 > radius * radius)
            return false;
        float thc = sqrtf(radius * radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0)
            t0 = t1;
        if (t0 < 0)
            return false;
        return true;
    }
};

bool scene_intersect(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, Vec3f &hit, Vec3f &N, Material &material)
{
    float spheres_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < spheres.size(); i++)
    {
        float dist_i;
        if (spheres[i].ray_intersect(orig, dir, dist_i) && dist_i < spheres_dist)
        {
            spheres_dist = dist_i;
            hit = orig + dir * dist_i;
            N = (hit - spheres[i].center).normalize();
            material = spheres[i].material;
        }
    }
    return spheres_dist < 1000;
}

RGB cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, const std::vector<Light> &lights)
{
    Vec3f point, N;
    Material material;

    if (!scene_intersect(orig, dir, spheres, point, N, material))
    {
        return RGB{
            (uint8_t)(0.2 * 255),
            (uint8_t)(0.7 * 255),
            (uint8_t)(0.8 * 255),
        }; // background color
    }

    float diffuse_light_intensity = 0;

    for (size_t i = 0; i < lights.size(); i++)
    {
        Vec3f light_dir = (lights[i].position - point).normalize();
        diffuse_light_intensity += lights[i].intensity * std::max(0.f, light_dir * N);
    }

    Vec3f diffuse_color = material.diffuse_color * diffuse_light_intensity;

    return RGB{
        (uint8_t)(diffuse_color.x * 255),
        (uint8_t)(diffuse_color.y * 255),
        (uint8_t)(diffuse_color.z * 255),
    };
}

#endif