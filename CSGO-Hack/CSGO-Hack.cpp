#include <iostream>
#include <list>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include "Offsets.h"
#include "Memory.h"
#include "SharedDefines.h"

// Max FOV for starting aiming
float MaxFOV = 2.f;

// Higher value = faster aiming
float Smooth = 4.0f;

auto start = std::chrono::high_resolution_clock::now();
Vector3 initialAngles;
float lerp = 0.f;

void Aimbot()
{
    Localplayer* me = SharedDefines::localPlayer;

    if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && me->IsAlive())
    {
        const auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = now - start;

        // Only run for 1 second max
        if (elapsed.count() > 1.0f)
            return;

        const Vector3 myAngles = me->GetViewAngles();
        const Vector3 myViewPunch = me->GetPunchAngles() * me->GetPunchRand();
        const Vector3 myEyePos = me->GetEyePosition() + me->GetPosition();

        if (!me->HasTarget() && !me->IsUsingPistol())
        {
            // Should choose target closest to crosshair
            Entity* closestTarget = nullptr;
            float closestTargetFOV = 1000000.f;
            int closestTargetBone = 7;

            for (int i = 0; i < 64; i++)
            {
                Entity* currentEntity = new Entity(i);
                float closestFOV = 1000000.f;
                int closestBone = 7;

                if (currentEntity->IsValid())
                {
                    if (currentEntity->GetTeam() != me->GetTeam() && !currentEntity->IsImmune())
                    {
                        for (auto j : { BONE_STOMACH, BONE_CHEST, BONE_UPPER_CHEST, BONE_NECK, BONE_FACE })
                        {
                            const Vector3 bonePos = currentEntity->GetBonePosition(j);
                            Vector3 boneAngle = CalcAngle(myEyePos, bonePos);
                            Vector3 deltaAngle = myAngles + myViewPunch - boneAngle;
                            Clamp(deltaAngle);

                            float FOV = fabsf(deltaAngle.x) + fabsf(deltaAngle.y);

                            if (FOV < closestFOV && SharedDefines::BSP->IsVisible(myEyePos, bonePos))
                            {
                                closestFOV = FOV;
                                closestBone = j;
                            }
                        }

                        if (closestFOV < MaxFOV && closestFOV < closestTargetFOV)
                        {
                            closestTargetFOV = closestFOV;
                            closestTarget = currentEntity;
                            closestTargetBone = closestBone;
                        }
                    }
                }

                if (me->GetTarget() != currentEntity && closestTarget != currentEntity)
                    delete currentEntity;
            }

            // Set the target if we found a new close one
            if (closestTarget != nullptr)
            {
                start = std::chrono::high_resolution_clock::now();
                initialAngles = me->GetViewAngles();
                me->SetTarget(closestTarget);
                me->SetTargetBone(closestTargetBone);
                me->SetPunchRand((2.2f - 1.8f) * (static_cast<float>(rand()) / RAND_MAX) + 1.8f);
            }
        }
        else if (me->GetTarget() != nullptr && me->GetTarget()->IsValid())
        {
            if (me->IsUsingWeapon())
            {
                const Vector3 targetPos = me->GetTarget()->GetBonePosition(me->GetTargetBone());
                if (SharedDefines::BSP->IsVisible(myEyePos, targetPos))
                {
                    const Vector3 targetAngle = CalcAngle(myEyePos, targetPos);

                    float lerp = elapsed.count() * Smooth;
                    if (lerp > 1.0f)
                        lerp = 1.0f;

                    lerp = SmoothStep(lerp);
                    // lerp = InversePower(lerp, 2.4f);

                    Vector3 deltaAngle = targetAngle - initialAngles - myViewPunch;
                    Clamp(deltaAngle);

                    // Cubic Bezier (doesn't quite work yet, but basic idea)
                    /*Vector3 p1 = Vector3(initialAngles.x - deltaAngle.x * 0.25f, initialAngles.y + deltaAngle.y * 0.25f, 0.f);
                    Vector3 p2 = Vector3(initialAngles.x + deltaAngle.x * 1.25f, initialAngles.y + deltaAngle.y * 0.75f, 0.f);
                    Vector3 destination = CubicBezier(initialAngles, p1, p2, targetAngle - myViewPunch, lerp);*/

                    // SmoothStep
                    Vector3 destination = initialAngles + (deltaAngle * lerp);

                    const float FOV = fabsf(deltaAngle.x) + fabsf(deltaAngle.y);

                    // SMAC Aimbot Detection (LUL)
                    if (FOV < 35)
                    {
                        Clamp(destination);
                        me->SetViewAngles(destination);
                    }
                }
            }
        }
        else
            me->SetTarget(nullptr);
    }
    else if (me->GetTarget() != nullptr) 
    {
        me->SetTarget(nullptr);
    }
    else
    {
        start = std::chrono::high_resolution_clock::now();
        initialAngles = me->GetViewAngles();
    }
}

void Wallhack()
{
    Localplayer* me = SharedDefines::localPlayer;
    const DWORD glowPointer = SharedDefines::localPlayer->GetGlowPointer();
    const Vector3 myEyePos = me->GetPosition() + me->GetEyePosition();

    for (int i = 0; i < 64; i++)
    {
        Entity* currentEntity = new Entity(i);

        if (currentEntity->IsValid())
        {
            const Vector3 entityPos = currentEntity->GetPosition() + currentEntity->GetEyePosition();

            switch (currentEntity->GetTeam())
            {
            case 2: // T
                if (SharedDefines::BSP->IsVisible(myEyePos, entityPos))
                    currentEntity->SetGlow(glowPointer, 0.878431f, 0.686275f, 0.337255f, 0.4f);
                else
                    currentEntity->SetGlow(glowPointer, 0.878431f, 0.686275f, 0.337255f, 0.6f);
                break;
            case 3: // CT
                if (SharedDefines::BSP->IsVisible(myEyePos, entityPos))
                    currentEntity->SetGlow(glowPointer, 0.447059f, 0.607843f, 0.866667f, 0.4f);
                else
                    currentEntity->SetGlow(glowPointer, 0.447059f, 0.607843f, 0.866667f, 0.6f);
                break;
            default:
                break;
            }
        }
        delete currentEntity;
    }
}

// Ghetto Triggerbot (please parse models and hitboxes)
void Triggerbot()
{
    Localplayer* me = SharedDefines::localPlayer;

    // Hold down #6 (0x36 = 6 in ascii)
    if ((GetKeyState(0x36) & 0x100) != 0 && me->IsAlive())
    {
        if (SharedDefines::entityInCross != nullptr)
        {
            if (SharedDefines::entityInCross->IsValid())
            {
                if (SharedDefines::entityInCross->GetTeam() != me->GetTeam() && me->CanShoot() && !SharedDefines::entityInCross->IsImmune())
                {
                    me->Shoot();
                }
            }
        }
    }
}

bool LoadMap(std::string map)
{
    char buff[FILENAME_MAX];
    _getcwd(buff, FILENAME_MAX);
    const std::string currentWorkingDir(buff);
    std::string mapPath = currentWorkingDir + "\\maps\\" + map + ".bsp";

    if (SharedDefines::BSP->Load(mapPath.c_str(), map.c_str()))
        return true;

    return false;
}

int main()
{
    std::cout << "Welcome to feed city" << std::endl;
    std::cout << "====================" << std::endl << std::endl;

    if (!SharedDefines::InitializeModules())
    {
        std::cout << "Couldn't attach to CS:GO" << std::endl;
        system("pause");
        exit(0);
    }

    SharedDefines::InitializeObjects();

    std::cout << "Successfully hooked CS:GO" << std::endl;

    std::cout << "Scanning for signatures" << std::endl;
    if (Offsets::Signatures::UpdateSignatures())
    {
        std::cout << "Found all signatures" << std::endl;
    }
    else
    {
        std::cout << "Scanning incomplete. Couldn't find offsets." << std::endl;
        system("pause");
        exit(0);
    }

    // TODO: Implement netvars
    // std::cout << "Scanning for netvars" << std::endl;
    // std::cout << "Found all netvars" << std::endl << std::endl;

    srand(static_cast<int>(time(nullptr)));
    std::string mapName = "";

    // Hack loop
    while (true)
    {
        SharedDefines::localPlayer->Update();
        std::string curMap = SharedDefines::localPlayer->GetCurrentMap();
        if (curMap != mapName)
        {
            mapName = curMap;
            if (curMap.length() > 0)
            {
                std::cout << "Changing map to " << mapName.c_str() << std::endl;
                if (!LoadMap(mapName))
                {
                    std::cout << "Failed to change map. Please make sure that map files exists." << std::endl;
                }
            }
            else
            {
                std::cout << "Unloaded map" << std::endl;
                SharedDefines::BSP->Unload();
            }
        }
        
        Wallhack();
        Aimbot();
        Triggerbot();
    }
}
