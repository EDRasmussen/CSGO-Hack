#include "SharedDefines.h"

namespace SharedDefines
{
    DWORD engineModule;
    DWORD clientModule;
    DWORD engineModuleSize;
    DWORD clientModuleSize;
    Memory memory;
    Localplayer* localPlayer;
    Entity* entityInCross;
    BSPParser* BSP;

    bool InitializeModules()
    {
        memory.AttachToProcess("csgo.exe");
        engineModule = memory.Module("engine.dll");
        clientModule = memory.Module("client_panorama.dll");
        clientModuleSize = memory.GetModuleSize("client_panorama.dll");
        engineModuleSize = memory.GetModuleSize("engine.dll");

        return !(engineModule == 0 || clientModule == 0);
    }

    bool InitializeObjects()
    {
        localPlayer = new Localplayer();
        BSP = new BSPParser();
        return true;
    }
}
