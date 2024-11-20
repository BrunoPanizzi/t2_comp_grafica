#ifndef vec3_h
#define vec3_h

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

Vec3 newVec3(float x, float y, float z);

Vec3 vec3Add(Vec3 a, Vec3 b);
Vec3 vec3Sub(Vec3 a, Vec3 b);
Vec3 vec3Scale(Vec3 v, float scalar);
float vec3Dot(Vec3 a, Vec3 b);
Vec3 vec3Cross(Vec3 a, Vec3 b);
float vec3Length(Vec3 v);
Vec3 vec3Normalize(Vec3 v);


#ifdef vec3_impl

#include <math.h>


Vec3 newVec3(float x, float y, float z) {
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vec3 vec3Add(Vec3 a, Vec3 b) {
    return newVec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 vec3Sub(Vec3 a, Vec3 b) {
    return newVec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 vec3Scale(Vec3 v, float scalar) {
    return newVec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

float vec3Dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3Cross(Vec3 a, Vec3 b) {
    return newVec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float vec3Length(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3Normalize(Vec3 v) {
    float len = vec3Length(v);
    if (len == 0) {
        return newVec3(0, 0, 0);
    }
    return vec3Scale(v, 1.0f / len);
}

#endif // vec3_impl

#endif // vec3_h
