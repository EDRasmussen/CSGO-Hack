#include "Offsets.h"
#include "SharedDefines.h"

namespace Offsets 
{
    namespace Signatures
    {
        DWORD dwLocalPlayer;
        DWORD dwGlobalVars;
        DWORD dwEntityList;
        DWORD dwClientState;
        DWORD dwGlowObjectManager;
        DWORD dwForceAttack;
        DWORD dwClientState_ViewAngles;
        DWORD dwClientState_Map;

        bool UpdateSignatures()
        {
            dwLocalPlayer = SharedDefines::memory.FindPattern("client", "\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF", "xxx????xx????xxxxxxxxx", 3, 4);
            dwGlobalVars = SharedDefines::memory.FindPattern("engine", "\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\xFF\x50\x08\x85\xC0", "x????x????xxxxx", 1, 0);
            dwEntityList = SharedDefines::memory.FindPattern("client", "\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8", "x????xxxxx????xx", 1, 0);
            dwClientState = SharedDefines::memory.FindPattern("engine", "\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0", "x????xxxxxxxxxx", 1, 0);
            dwGlowObjectManager = SharedDefines::memory.FindPattern("client", "\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B", "x????xxxx", 1, 4);
            dwForceAttack = SharedDefines::memory.FindPattern("client", "\x89\x0D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\xF2\x8B\xC1\x83\xCE\x04", "xx????xx????xxxxxxx", 2, 0);
            dwClientState_ViewAngles = SharedDefines::memory.FindPattern("engine", "\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05", "xxxx????xxxxx", 4, 0, false);
            dwClientState_Map = SharedDefines::memory.FindPattern("engine", "\x05\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xA1", "x????xxxxxxxxx", 1, 0, false);

            std::cout << "OffsetName               : " << "Expected" << " / " << "Actual" << std::endl;
            std::cout << "dwLocalPlayer            : " << dwLocalPlayer << " / " << DWORD(0xCD2764) << std::endl;
            std::cout << "dwGlobalVars             : " << dwGlobalVars << " / " << DWORD(0x58BA00) << std::endl;
            std::cout << "dwEntityList             : " << dwEntityList << " / " << DWORD(0x4CE34DC) << std::endl;
            std::cout << "dwClientState            : " << dwClientState << " / " << DWORD(0x58BCFC) << std::endl;
            std::cout << "dwGlowObjectManager      : " << dwGlowObjectManager << " / " << DWORD(0x5223730) << std::endl;
            std::cout << "dwForceAttack            : " << dwForceAttack << " / " << DWORD(0x3114BA4) << std::endl;
            std::cout << "dwClientState_ViewAngles : " << dwClientState_ViewAngles << " / " << DWORD(0x4D88) << std::endl;
            std::cout << "dwClientState_Map        : " << dwClientState_Map << " / " << DWORD(0x28C) << std::endl;

            // Check everything
            return !(dwLocalPlayer == 0 || dwGlobalVars == 0 || dwEntityList == 0 || dwClientState == 0 ||
                dwGlowObjectManager == 0 || dwForceAttack == 0 || dwClientState_ViewAngles == 0 || dwClientState_Map ==
                0);
        }
    }
}
