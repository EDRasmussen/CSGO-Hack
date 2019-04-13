#include "CSMath.h"

Vector3 CalcAngle(const Vector3 eyePos, const Vector3 targetPos)
{
    const Vector3 relativePosition = eyePos - targetPos;
    const float hyp = sqrtf(relativePosition.x * relativePosition.x + relativePosition.y * relativePosition.y);

    Vector3 placeToGo = Vector3(
        asinf(relativePosition.z / hyp) * 180 / 3.1415926535f,
        atanf(relativePosition.y / relativePosition.x) * 180 / 3.1415926535f,
        0.f
    );

    if (relativePosition.x >= 0.0f)
        placeToGo.y += 180.0f;

    return placeToGo;
}

void Normalize(Vector3 &angles) {
    while (angles.x > 89.0f) {
        angles.x -= 180.f;
    }

    while (angles.x < -89.0f) {
        angles.x += 180.f;
    }

    while (angles.y > 180.f) {
        angles.y -= 360.f;
    }

    while (angles.y < -180.f) {
        angles.y += 360.f;
    }
}

void ClampAngles(Vector3 &angles)
{
    if (angles.y > 180.0f)
        angles.y = 180.0f;
    else if (angles.y < -180.0f)
        angles.y = -180.0f;

    if (angles.x > 89.0f)
        angles.x = 89.0f;
    else if (angles.x < -89.0f)
        angles.x = -89.0f;

    angles.z = 0;
}

void Clamp(Vector3 &angles)
{
    Normalize(angles);
    ClampAngles(angles);
}

float SmoothStep(const float x) 
{
    // Evaluate polynomial
    return x * x * (3.f - 2.f * x);
}

float InversePower(const float x, const float power)
{
    return powf(x, 1/power);
}

Vector3 CubicBezier(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, float t)
{
    return p0 * powf(1 - t, 3.f) + p1 * 3 * powf(1 - t, 2.f) * t + p2 * 3 * (1 - t) * powf(t, 2.f) + p3 * powf(t, 3.f);
}
