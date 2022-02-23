#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "geometry.h"
#include <cmath>
#include <limits>


struct Sphere {
    vec3 center;
    float radius;

    Sphere(const vec3 &c, const float &r) : center(c), radius(r) {}

    bool ray_intersect(const vec3 &orig, const vec3 &dir, float &t0) const {
        vec3 L = center - orig;
        float tca = L*dir;
        float d2 = L*L - tca*tca;
        if (d2 > radius*radius) return false;
        float thc = sqrtf(radius*radius - d2);
        t0 = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
};

RGB cast_ray(const vec3 &orig, const vec3 &dir, const Sphere &sphere) {
    float sphere_dist = std::numeric_limits<float>::max();
    if (sphere.ray_intersect(orig, dir, sphere_dist)) {
        return RGB {0, 255, 0}; // green
    }
    return RGB {0, 0, 255}; // background color blue
}


#endif