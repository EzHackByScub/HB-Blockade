#pragma once
#include <math.h>

struct Matrix4x4 {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        }; float m[4][4];
    };
};
class Vec2
{
public:
	float x, y;
};

class Vec3
{
public:
	float x, y, z;
    inline float Dot(Vec3 v)
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline float Distance(Vec3 v)
    {
        return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
    }
};
