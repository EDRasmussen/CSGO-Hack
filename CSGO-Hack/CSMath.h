#pragma once

#include <cmath>

class Vector3
{
public:
    float x, y, z;

    Vector3()
    {
        x = y = z = 0.0f;
    }

    Vector3(float X, float Y, float Z)
    {
        x = X; y = Y; z = Z;
    }

    Vector3(float XYZ)
    {
        x = XYZ; y = XYZ; z = XYZ;
    }

    Vector3(float* v)
    {
        x = v[0]; y = v[1]; z = v[2];
    }

    Vector3(const float* v)
    {
        x = v[0]; y = v[1]; z = v[2];
    }

   Vector3& operator=(const Vector3& v)
    {
        x = v.x; y = v.y; z = v.z; return *this;
    }

    Vector3& operator=(const float* v)
    {
        x = v[0]; y = v[1]; z = v[2]; return *this;
    }

    float& operator[](int i)
    {
        return ((float*)this)[i];
    }

    float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    Vector3& operator+=(const Vector3& v)
    {
        x += v.x; y += v.y; z += v.z; return *this;
    }

    Vector3& operator-=(const Vector3& v)
    {
        x -= v.x; y -= v.y; z -= v.z; return *this;
    }

    Vector3& operator*=(const Vector3& v)
    {
        x *= v.x; y *= v.y; z *= v.z; return *this;
    }

    Vector3& operator/=(const Vector3& v)
    {
        x /= v.x; y /= v.y; z /= v.z; return *this;
    }

    Vector3& operator+=(float v)
    {
        x += v; y += v; z += v; return *this;
    }

    Vector3& operator-=(float v)
    {
        x -= v; y -= v; z -= v; return *this;
    }

    Vector3& operator*=(float v)
    {
        x *= v; y *= v; z *= v; return *this;
    }

    Vector3& operator/=(float v)
    {
        x /= v; y /= v; z /= v; return *this;
    }

    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(const Vector3& v) const
    {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    Vector3 operator/(const Vector3& v) const
    {
        return Vector3(x / v.x, y / v.y, z / v.z);
    }

    Vector3 operator+(float v) const
    {
        return Vector3(x + v, y + v, z + v);
    }

    Vector3 operator-(float v) const
    {
        return Vector3(x - v, y - v, z - v);
    }

    Vector3 operator*(float v) const
    {
        return Vector3(x * v, y * v, z * v);
    }

    Vector3 operator/(float v) const
    {
        return Vector3(x / v, y / v, z / v);
    }

    float Length() const
    {
        return sqrtf(x * x + y * y + z * z);
    }

    float LengthSqr() const
    {
        return (x * x + y * y + z * z);
    }

    float LengthXY() const
    {
        return sqrtf(x * x + y * y);
    }

    float LengthXZ() const
    {
        return sqrtf(x * x + z * z);
    }

    float DistTo(const Vector3& v) const
    {
        return (*this - v).Length();
    }

    float Dot(const Vector3& v) const
    {
        return (x * v.x + y * v.y + z * v.z);
    }

    float Diff(const Vector3& v) const
    {
        return fabsf(x - v.x) + fabsf(y - v.y);
    }

    Vector3 Cross(const Vector3& v) const
    {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    bool IsZero() const
    {
        return (x > -0.01f && x < 0.01f
            &&	y > -0.01f && y < 0.01f
            &&	z > -0.01f && z < 0.01f);
    }

    void Reset()
    {
        x = 0.f; y = 0.f; z = 0.f;
    }
};


Vector3 CalcAngle(Vector3 eyePos, Vector3 targetPos);
void Normalize(Vector3 &angle);
void ClampAngles(Vector3 &angles);
void Clamp(Vector3 &angles);
float SmoothStep(float x);
float InversePower(float x, float power);
Vector3 CubicBezier(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, float t);
