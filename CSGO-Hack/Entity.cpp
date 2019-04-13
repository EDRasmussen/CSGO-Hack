#include "Entity.h"
#include "SharedDefines.h"
#include "Offsets.h"

Entity::Entity(const int index)
{
    if (index < 0)
        m_dwBaseAddress = 0;
    else
        m_dwBaseAddress = SharedDefines::memory.Read<DWORD>(SharedDefines::clientModule + Offsets::Signatures::dwEntityList + index * 0x10);
}

Entity::Entity() { }
Entity::~Entity() { }

void Entity::Update()
{
    m_dwBaseAddress = SharedDefines::memory.Read<DWORD>(SharedDefines::clientModule + Offsets::Signatures::dwLocalPlayer);
    const DWORD m_dwWeaponHandle = SharedDefines::memory.Read<DWORD>(m_dwBaseAddress + Offsets::Netvars::m_hActiveWeapon);
    const DWORD m_dwWeaponEntId = m_dwWeaponHandle & 0xFFF;
    m_dwWeaponAddress = SharedDefines::memory.Read<DWORD>(SharedDefines::clientModule + Offsets::Signatures::dwEntityList + (m_dwWeaponEntId - 1) * 0x10);

    const int InCross = SharedDefines::memory.Read<int>(m_dwBaseAddress + Offsets::Netvars::m_iCrosshairId);
    if (InCross > 0 && InCross <= 64)
    {
        m_iCrosshairID = InCross - 1;
        delete SharedDefines::entityInCross;
        SharedDefines::entityInCross = new Entity(m_iCrosshairID);
    }
    else
    {
        m_iCrosshairID = -1;
        delete SharedDefines::entityInCross;
        SharedDefines::entityInCross = nullptr;
    }
}

int Entity::GetHealth() const
{
    return SharedDefines::memory.Read<int>(m_dwBaseAddress + Offsets::Netvars::m_iHealth);
}

int Entity::GetLifestate() const
{
    return SharedDefines::memory.Read<int>(m_dwBaseAddress + Offsets::Netvars::m_lifeState);
}

int Entity::GetTeam() const
{
    return SharedDefines::memory.Read<int>(m_dwBaseAddress + Offsets::Netvars::m_iTeamNum);
}

int Entity::GetCrosshairID() const
{
    return m_iCrosshairID;
}

int Entity::GetWeaponID() const
{
    return SharedDefines::memory.Read<short>(m_dwWeaponAddress + Offsets::Netvars::m_iItemDefinitionIndex);
}

int Entity::GetAmmo() const
{
    return SharedDefines::memory.Read<int>(m_dwWeaponAddress + Offsets::Netvars::m_iClip1);
}

DWORD Entity::GetBaseAddress() const
{
    return m_dwBaseAddress;
}

DWORD Entity::GetGlowIndex() const
{
    return SharedDefines::memory.Read<int>(m_dwBaseAddress + Offsets::Netvars::m_iGlowIndex);
}

DWORD Entity::GetEnginePointer() const
{
    return SharedDefines::memory.Read<DWORD>(SharedDefines::engineModule + Offsets::Signatures::dwClientState);
}

DWORD Entity::GetGlowPointer() const
{
    return SharedDefines::memory.Read<DWORD>(SharedDefines::clientModule + Offsets::Signatures::dwGlowObjectManager);
}

DWORD Entity::GetWeaponAddress() const
{
    return m_dwWeaponAddress;
}

float Entity::GetIntervalPerTick() const
{
    return SharedDefines::memory.Read<float>(SharedDefines::engineModule + Offsets::Signatures::dwGlobalVars + 0x20);
}

float Entity::GetServerTime()
{
    return SharedDefines::memory.Read<float>(SharedDefines::engineModule + Offsets::Signatures::dwGlobalVars + 0x10);
}

float Entity::GetNextPrimaryAttack() const
{
    return SharedDefines::memory.Read<float>(m_dwWeaponAddress + Offsets::Netvars::m_flNextPrimaryAttack);
}

bool Entity::IsValid()
{
    if (this == nullptr)
        return false;

    return m_dwBaseAddress > 0 && m_dwBaseAddress != SharedDefines::localPlayer->GetBaseAddress() && IsAlive() && IsDormant();
}

bool Entity::IsAlive() const
{
    return GetHealth() > 0 && GetLifestate() == LIFE_ALIVE;
}

// TODO: Fix
bool Entity::IsDormant() const
{
    return true;
}

bool Entity::IsImmune() const
{
    return SharedDefines::memory.Read<bool>(m_dwBaseAddress + Offsets::Netvars::m_bGunGameImmunity);
}

bool Entity::CanShoot()
{
    const float attackTime = GetNextPrimaryAttack();
    const float serverTime = GetServerTime();

    return !(attackTime > serverTime || GetAmmo() <= 0);
}

bool Entity::IsUsingPistol() const
{
    const int weaponID = GetWeaponID();

    return weaponID == WEAPON_DEAGLE ||
        weaponID == WEAPON_ELITE ||
        weaponID == WEAPON_FIVESEVEN ||
        weaponID == WEAPON_GLOCK ||
        weaponID == WEAPON_USP_SILENCER ||
        weaponID == WEAPON_TEC9 ||
        weaponID == WEAPON_P250;
}

bool Entity::IsUsingSniper() const
{
    const int weaponID = GetWeaponID();

    return weaponID == WEAPON_AWP ||
        weaponID == WEAPON_G3SG1 ||
        weaponID == WEAPON_SCAR20 ||
        weaponID == WEAPON_SSG08;
}

bool Entity::IsUsingWeapon() const
{
    const int weaponID = GetWeaponID();

    return weaponID != ITEM_NONE &&
        weaponID != WEAPON_KNIFE &&
        weaponID != WEAPON_C4 &&
        weaponID != WEAPON_DECOY &&
        weaponID != WEAPON_FLASHBANG &&
        weaponID != WEAPON_HEGRENADE &&
        weaponID != WEAPON_INCGRENADE &&
        weaponID != WEAPON_MOLOTOV &&
        weaponID != WEAPON_SMOKEGRENADE &&
        weaponID != WEAPON_TASER &&
        weaponID != WEAPON_KNIFE_T &&
        weaponID != WEAPON_KNIFE_BAYONET &&
        weaponID != WEAPON_KNIFE_FLIP &&
        weaponID != WEAPON_KNIFE_GUT &&
        weaponID != WEAPON_KNIFE_KARAMBIT &&
        weaponID != WEAPON_KNIFE_M9_BAYONET &&
        weaponID != WEAPON_KNIFE_TACTICAL &&
        weaponID != WEAPON_KNIFE_FALCHION &&
        weaponID != WEAPON_KNIFE_SURVIVAL_BOWIE &&
        weaponID != WEAPON_KNIFE_BUTTERFLY &&
        weaponID != WEAPON_KNIFE_PUSH;
}

Vector3 Entity::GetBonePosition(const int bone) const
{
    const DWORD boneMatrix = SharedDefines::memory.Read<DWORD>(m_dwBaseAddress + Offsets::Netvars::m_dwBoneMatrix);
    return Vector3(
        SharedDefines::memory.Read<float>(boneMatrix + 0x30 * bone + 0x0c),
        SharedDefines::memory.Read<float>(boneMatrix + 0x30 * bone + 0x1c),
        SharedDefines::memory.Read<float>(boneMatrix + 0x30 * bone + 0x2c)
    );
}

Vector3 Entity::GetVelocity() const
{
    return SharedDefines::memory.Read<Vector3>(m_dwBaseAddress + Offsets::Netvars::m_vecVelocity);
}

Vector3 Entity::GetPosition() const
{
    return SharedDefines::memory.Read<Vector3>(m_dwBaseAddress + Offsets::Netvars::m_vecOrigin);
}

Vector3 Entity::GetViewAngles() const
{
    return SharedDefines::memory.Read<Vector3>(GetEnginePointer() + Offsets::Signatures::dwClientState_ViewAngles);
}

Vector3 Entity::GetPunchAngles() const
{
    return SharedDefines::memory.Read<Vector3>(m_dwBaseAddress + Offsets::Netvars::m_aimPunchAngle);
}

Vector3 Entity::GetEyePosition() const
{
    return SharedDefines::memory.Read<Vector3>(m_dwBaseAddress + Offsets::Netvars::m_vecViewOffset);
}

void Entity::SetGlow(const DWORD glowPointer, const float r, const float g, const float b, const float a) const
{
    const DWORD glowIndex = GetGlowIndex();
    SharedDefines::memory.Write<float>(glowPointer + (glowIndex * 0x38) + 0x4, r);
    SharedDefines::memory.Write<float>(glowPointer + (glowIndex * 0x38) + 0x8, g);
    SharedDefines::memory.Write<float>(glowPointer + (glowIndex * 0x38) + 0xC, b);
    SharedDefines::memory.Write<float>(glowPointer + (glowIndex * 0x38) + 0x10, a);
    SharedDefines::memory.Write<bool>(glowPointer + (glowIndex * 0x38) + 0x24, true);
    SharedDefines::memory.Write<bool>(glowPointer + (glowIndex * 0x38) + 0x25, false);
}
