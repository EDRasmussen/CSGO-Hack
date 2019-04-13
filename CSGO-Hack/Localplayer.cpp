#include "Localplayer.h"
#include "Offsets.h"
#include "SharedDefines.h"

Localplayer::Localplayer()
{
}
Localplayer::~Localplayer()
{
}

void Localplayer::Shoot()
{
    SharedDefines::memory.Write<int>(SharedDefines::clientModule + Offsets::Signatures::dwForceAttack, 6);
}

void Localplayer::SetViewAngles(Vector3 Angles)
{
    SharedDefines::memory.Write<Vector3>(this->GetEnginePointer() + Offsets::Signatures::dwClientState_ViewAngles, Angles);
}

bool Localplayer::HasTarget()
{
    return this->GetTarget() != nullptr;
}

Entity* Localplayer::GetTarget()
{
    return target;
}

int Localplayer::GetTargetBone()
{
    return targetBone;
}

float Localplayer::GetPunchRand()
{
    return punchRand;
}

void Localplayer::SetTarget(Entity* targetEntity)
{
    target = targetEntity;
}

void Localplayer::SetTargetBone(int bone)
{
    targetBone = bone;
}

void Localplayer::SetPunchRand(float rand)
{
    punchRand = rand;
}

std::string Localplayer::GetCurrentMap()
{
    return SharedDefines::memory.ReadString(GetEnginePointer() + Offsets::Signatures::dwClientState_Map);
}
