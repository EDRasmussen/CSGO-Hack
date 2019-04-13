#pragma once

#include "Entity.h"
#include "CSMath.h"
#include <string>

class Localplayer : public Entity
{
public:
    Localplayer();
    ~Localplayer();

    void Shoot();
    void SetViewAngles(Vector3 Angles);
    void SetTarget(Entity* targetEntity);
    void SetTargetBone(int bone);
    void SetPunchRand(float rand);

    bool HasTarget();

    Entity* GetTarget();
    int GetTargetBone();
    float GetPunchRand();

    std::string GetCurrentMap();

private:
    Entity* target = nullptr;
    int targetBone = 7;
    float punchRand = 1.986f;
};
