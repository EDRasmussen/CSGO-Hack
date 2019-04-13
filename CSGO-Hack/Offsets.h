#pragma once

#include <cstddef>
#include <Windows.h>

namespace Offsets {
    namespace Netvars {
        constexpr ::std::ptrdiff_t cs_gamerules_data = 0x0;
        constexpr ::std::ptrdiff_t m_ArmorValue = 0xB328;
        constexpr ::std::ptrdiff_t m_Collision = 0x31C;
        constexpr ::std::ptrdiff_t m_CollisionGroup = 0x474;
        constexpr ::std::ptrdiff_t m_Local = 0x2FBC;
        constexpr ::std::ptrdiff_t m_MoveType = 0x25C;
        constexpr ::std::ptrdiff_t m_OriginalOwnerXuidHigh = 0x31B4;
        constexpr ::std::ptrdiff_t m_OriginalOwnerXuidLow = 0x31B0;
        constexpr ::std::ptrdiff_t m_SurvivalGameRuleDecisionTypes = 0x1320;
        constexpr ::std::ptrdiff_t m_SurvivalRules = 0xCF8;
        constexpr ::std::ptrdiff_t m_aimPunchAngle = 0x302C;
        constexpr ::std::ptrdiff_t m_aimPunchAngleVel = 0x3038;
        constexpr ::std::ptrdiff_t m_angEyeAnglesX = 0xB32C;
        constexpr ::std::ptrdiff_t m_angEyeAnglesY = 0xB330;
        constexpr ::std::ptrdiff_t m_bBombPlanted = 0x99D;
        constexpr ::std::ptrdiff_t m_bFreezePeriod = 0x20;
        constexpr ::std::ptrdiff_t m_bGunGameImmunity = 0x3928;
        constexpr ::std::ptrdiff_t m_bHasDefuser = 0xB338;
        constexpr ::std::ptrdiff_t m_bHasHelmet = 0xB31C;
        constexpr ::std::ptrdiff_t m_bInReload = 0x3285;
        constexpr ::std::ptrdiff_t m_bIsDefusing = 0x3914;
        constexpr ::std::ptrdiff_t m_bIsQueuedMatchmaking = 0x74;
        constexpr ::std::ptrdiff_t m_bIsScoped = 0x390A;
        constexpr ::std::ptrdiff_t m_bIsValveDS = 0x75;
        constexpr ::std::ptrdiff_t m_bSpotted = 0x93D;
        constexpr ::std::ptrdiff_t m_bSpottedByMask = 0x980;
        constexpr ::std::ptrdiff_t m_bStartedArming = 0x33C0;
        constexpr ::std::ptrdiff_t m_clrRender = 0x70;
        constexpr ::std::ptrdiff_t m_dwBoneMatrix = 0x26A8;
        constexpr ::std::ptrdiff_t m_fAccuracyPenalty = 0x3304;
        constexpr ::std::ptrdiff_t m_fFlags = 0x104;
        constexpr ::std::ptrdiff_t m_flC4Blow = 0x2990;
        constexpr ::std::ptrdiff_t m_flDefuseCountDown = 0x29AC;
        constexpr ::std::ptrdiff_t m_flDefuseLength = 0x29A8;
        constexpr ::std::ptrdiff_t m_flFallbackWear = 0x31C0;
        constexpr ::std::ptrdiff_t m_flFlashDuration = 0xA3E0;
        constexpr ::std::ptrdiff_t m_flFlashMaxAlpha = 0xA3DC;
        constexpr ::std::ptrdiff_t m_flLastBoneSetupTime = 0x2924;
        constexpr ::std::ptrdiff_t m_flLowerBodyYawTarget = 0x3A74;
        constexpr ::std::ptrdiff_t m_flNextAttack = 0x2D70;
        constexpr ::std::ptrdiff_t m_flNextPrimaryAttack = 0x3218;
        constexpr ::std::ptrdiff_t m_flSimulationTime = 0x268;
        constexpr ::std::ptrdiff_t m_flTimerLength = 0x2994;
        constexpr ::std::ptrdiff_t m_hActiveWeapon = 0x2EF8;
        constexpr ::std::ptrdiff_t m_hMyWeapons = 0x2DF8;
        constexpr ::std::ptrdiff_t m_hObserverTarget = 0x3388;
        constexpr ::std::ptrdiff_t m_hOwner = 0x29CC;
        constexpr ::std::ptrdiff_t m_hOwnerEntity = 0x14C;
        constexpr ::std::ptrdiff_t m_iAccountID = 0x2FC8;
        constexpr ::std::ptrdiff_t m_iClip1 = 0x3244;
        constexpr ::std::ptrdiff_t m_iCompetitiveRanking = 0x1A84;
        constexpr ::std::ptrdiff_t m_iCompetitiveWins = 0x1B88;
        constexpr ::std::ptrdiff_t m_iCrosshairId = 0xB394;
        constexpr ::std::ptrdiff_t m_iEntityQuality = 0x2FAC;
        constexpr ::std::ptrdiff_t m_iFOV = 0x31E4;
        constexpr ::std::ptrdiff_t m_iFOVStart = 0x31E8;
        constexpr ::std::ptrdiff_t m_iGlowIndex = 0xA3F8;
        constexpr ::std::ptrdiff_t m_iHealth = 0x100;
        constexpr ::std::ptrdiff_t m_iItemDefinitionIndex = 0x2FAA;
        constexpr ::std::ptrdiff_t m_iItemIDHigh = 0x2FC0;
        constexpr ::std::ptrdiff_t m_iMostRecentModelBoneCounter = 0x2690;
        constexpr ::std::ptrdiff_t m_iObserverMode = 0x3374;
        constexpr ::std::ptrdiff_t m_iShotsFired = 0xA370;
        constexpr ::std::ptrdiff_t m_iState = 0x3238;
        constexpr ::std::ptrdiff_t m_iTeamNum = 0xF4;
        constexpr ::std::ptrdiff_t m_lifeState = 0x25F;
        constexpr ::std::ptrdiff_t m_nFallbackPaintKit = 0x31B8;
        constexpr ::std::ptrdiff_t m_nFallbackSeed = 0x31BC;
        constexpr ::std::ptrdiff_t m_nFallbackStatTrak = 0x31C4;
        constexpr ::std::ptrdiff_t m_nForceBone = 0x268C;
        constexpr ::std::ptrdiff_t m_nTickBase = 0x342C;
        constexpr ::std::ptrdiff_t m_rgflCoordinateFrame = 0x444;
        constexpr ::std::ptrdiff_t m_szCustomName = 0x303C;
        constexpr ::std::ptrdiff_t m_szLastPlaceName = 0x35B0;
        constexpr ::std::ptrdiff_t m_thirdPersonViewAngles = 0x31D8;
        constexpr ::std::ptrdiff_t m_vecOrigin = 0x138;
        constexpr ::std::ptrdiff_t m_vecVelocity = 0x114;
        constexpr ::std::ptrdiff_t m_vecViewOffset = 0x108;
        constexpr ::std::ptrdiff_t m_viewPunchAngle = 0x3020;
    }

    namespace Signatures {
        extern DWORD dwLocalPlayer;
        extern DWORD dwGlobalVars;
        extern DWORD dwEntityList;
        extern DWORD dwClientState;
        extern DWORD dwClientState_ViewAngles;
        extern DWORD dwGlowObjectManager;
        extern DWORD dwForceAttack;
        extern DWORD dwClientState_Map;

        bool UpdateSignatures();
    }
}
