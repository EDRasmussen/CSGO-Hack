#pragma once

#include <Windows.h>
#include "CSMath.h"

struct GlowStruct
{
    float r;
    float g;
    float b;
    float a;
    bool RenderWhenOccluded;
    bool RenderWhenUnoccluded;
};

class Entity
{
public:
    Entity(int index);
    Entity();
    ~Entity();

    int GetHealth() const;
    int GetLifestate() const;
    int GetTeam() const;
    int GetWeaponID() const;
    int GetAmmo() const;
    int GetCrosshairID() const;
    DWORD GetBaseAddress() const;
    DWORD GetGlowIndex() const;
    DWORD GetEnginePointer() const;
    DWORD GetGlowPointer() const;
    DWORD GetWeaponAddress() const;

    float GetIntervalPerTick() const;
    float GetServerTime();
    float GetNextPrimaryAttack() const;

    virtual bool IsValid();
    bool IsAlive() const;
    bool IsDormant() const;
    bool IsImmune() const;
    bool CanShoot();
    bool IsUsingPistol() const;
    bool IsUsingSniper() const;
    bool IsUsingWeapon() const;

    Vector3 GetBonePosition(int bone) const;
    Vector3 GetVelocity() const;
    Vector3 GetViewAngles() const;
    Vector3 GetEyePosition() const;
    Vector3 GetPosition() const;
    Vector3 GetPunchAngles() const;

    void SetGlow(DWORD glowPointer, float r, float g, float b, float a) const;
    void Update();

    DWORD m_dwBaseAddress;
private:
    int m_iCrosshairID;
    DWORD m_dwWeaponAddress;
};
