#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <cmath>

struct vec3 {
    float x = 0;
    float y = 0;
    float z = 0;

    // vec3(float &x, float &y, float &z) : x(x), y(y), z(z) {}


};

vec3 operator*(const vec3 &lhs, const float &rhs)
{
    vec3 ret;
    ret.x = lhs.x * rhs;
    ret.y = lhs.y * rhs;
    ret.z = lhs.z * rhs;
    
    return ret;
}

float operator*(const vec3 &lhs, const vec3 &rhs)
{
    float ret;
    ret += lhs.x * rhs.x;
    ret += lhs.y * rhs.y;
    ret += lhs.z * rhs.z;

    return ret;
}

vec3 operator+(vec3 &lhs, const vec3 &rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

vec3 operator-(const vec3 &lhs, const vec3 &rhs)
{
    vec3 ret;

    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    ret.z = lhs.z - rhs.z;
    return ret;
}

vec3 operator-(const vec3 &lhs)
{
    return lhs * (1.0f);
}

float norm(vec3 &vec)
{
    return std::sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
}

vec3 normalize(vec3 &vec, float l=1)
{
    return vec *(l/norm(vec));
}


#endif