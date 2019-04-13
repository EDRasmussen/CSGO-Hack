#include "Memory.h"
#include "SharedDefines.h"
#include <TlHelp32.h>
#include <comdef.h>

Memory::Memory()
{
}

Memory::~Memory()
{
    CloseHandle(hProcess);
}

HANDLE Memory::GetProcessHandle() const
{
    return hProcess;
}

DWORD Memory::GetProcessId() const
{
    return dwPID;
}

int Memory::CharSizeOfArray(char* chArray)
{
    for (int iLength = 1; iLength < MAX_PATH; iLength++)
        if (chArray[iLength] == '*')
            return iLength;

    std::cout << "Could not read array length\n";
    return 0;
}

int Memory::IntSizeOfArray(int *iArray)
{
    for (int iLength = 1; iLength < MAX_PATH; iLength++)
        if (iArray[iLength] == '*')
            return iLength;

    std::cout << "Could not read array length\n";
    return 0;
}

void Memory::AttachToProcess(const char* processName)
{
    const HANDLE hPid = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 procEntry;
    procEntry.dwSize = sizeof(procEntry);

    while (Process32Next(hPid, &procEntry)) 
    {
        _bstr_t tempProc(procEntry.szExeFile);
        if (!strcmp(tempProc, processName))
        {
            dwPID = procEntry.th32ProcessID;
            CloseHandle(hPid);

            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
            return;
        }
    }

    std::cout << "There was an issue attaching to CSGO.\n";
    system("pause");
    exit(0);
}

DWORD Memory::Module(const char* moduleName) const
{
    const HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(mEntry);

    while (Module32Next(hModule, &mEntry)) 
    {
        _bstr_t tempModule(mEntry.szModule);
        if (!strcmp(tempModule, moduleName))
        {
            CloseHandle(hModule);
            return DWORD(mEntry.modBaseAddr);
        }
    }

    return 0;
}

DWORD Memory::GetModuleSize(const char* module) const
{
    const HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(mEntry);

    while (Module32Next(hModule, &mEntry))
    {
        _bstr_t tempModule(mEntry.szModule);
        if (!strcmp(tempModule, module))
        {
            CloseHandle(hModule);
            return DWORD(mEntry.modBaseSize);
        }
    }

    return 0;
}

char* Memory::GetModuleFilename(const char* module) const
{
    MODULEENTRY32 xModule;
    const HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    xModule.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnap, &xModule)) {
        while (Module32Next(hSnap, &xModule)) {
            if (!strncmp((char*)xModule.szModule, module, 8)) {
                CloseHandle(hSnap);
                return _bstr_t(xModule.szExePath);
            }
        }
    }

    return 0;
}

uintptr_t Memory::FindPatternHelper(char* base, unsigned int size, const char* pattern, const char* mask)
{
    const size_t patternLength = strlen(mask);

    for (uintptr_t i = 0; i < size - patternLength; i++)
    {
        bool found = true;

        for (uintptr_t j = 0; j < patternLength; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)(base + i + j))
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            return (uintptr_t)base + i;
        }
    }

    return 0;
}

uintptr_t Memory::FindPattern(const char* module, const char* pattern, const char* mask, int offset, int extra, bool relative)
{
    DWORD start, end;

    if (module == "client")
    {
        start = SharedDefines::clientModule;
        end = start + SharedDefines::clientModuleSize;
    }
    else if (module == "engine")
    {
        start = SharedDefines::engineModule;
        end = start + SharedDefines::engineModuleSize;
    }
    else
        return 0;

    DWORD curChunk = start;
    SIZE_T bytesRead;

    while (curChunk < end)
    {
        byte buffer[4096];
        ReadProcessMemory(hProcess, LPCVOID(curChunk), &buffer, sizeof(buffer), &bytesRead);

        if (bytesRead == 0)
            return 0;

        uintptr_t internalAddr = FindPatternHelper((char*)&buffer, bytesRead, pattern, mask);

        if (internalAddr != 0)
        {
            uintptr_t offsetFromBuffer = internalAddr - (uintptr_t)&buffer;
            DWORD addr = curChunk + offsetFromBuffer;

            if (relative == false)
                return Read<DWORD>(addr + offset) + extra;

            return Read<DWORD>(addr + offset) - start + extra;
        }
        else
            curChunk += bytesRead;
    }

    return 0;
}
