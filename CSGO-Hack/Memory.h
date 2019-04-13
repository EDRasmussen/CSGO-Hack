#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>

class Memory
{
protected:
    HANDLE hProcess;
    DWORD dwPID, dwProtection, dwCaveAddress;

public:
    Memory();
    ~Memory();
    static int CharSizeOfArray(char* chArray);
    static int IntSizeOfArray(int* iArray);
    HANDLE GetProcessHandle() const;
    DWORD GetProcessId() const;

    std::string ReadString(DWORD dwAddress) const
    {
        // TODO: Add variable str length
        char buffer[128];
        ReadProcessMemory(hProcess, LPVOID(dwAddress), &buffer, 128, nullptr);

        int terminator = 0;
        for (int i = 0; i < 128; i++)
        {
            if (buffer[i] == '\0') 
            {
                terminator = i;
                break;
            }
        }
        std::string retStr(static_cast<char const*>(buffer), terminator);

        return retStr;
    }

    template <class CData>
    CData Read(DWORD dwAddress)
    {
        CData cRead;
        ReadProcessMemory(hProcess, (LPVOID)dwAddress, &cRead, sizeof(CData), nullptr);
        return cRead;
    }

    template <class CData>
    void Write(DWORD dwAddress, CData value)
    {
        WriteProcessMemory(hProcess, (LPVOID)dwAddress, &value, sizeof(CData), nullptr);
    }

    void AttachToProcess(const char* processName);
    DWORD Module(const char* moduleName) const;
    DWORD GetModuleSize(const char* module) const;
    char* GetModuleFilename(const char* module) const;

    uintptr_t FindPatternHelper(char* base, unsigned int size, const char* pattern, const char* mask);
    uintptr_t FindPattern(const char* module, const char* pattern, const char* mask, int offset, int extra, bool relative = true);
};
