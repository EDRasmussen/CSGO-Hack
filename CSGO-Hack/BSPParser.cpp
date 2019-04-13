#include "BSPParser.h"
#include <iostream>

BSPParser::~BSPParser() { }

void BSPParser::Unload()
{
    delete[]   m_data;

    *m_path = NULL;
    *m_mapName = NULL;
    m_header = nullptr;
    m_plane = nullptr;
    m_node = nullptr;
    m_leaf = nullptr;
}

bool BSPParser::IsNull()
{
    if (m_data == nullptr)
        return true;
    if (*m_path == NULL)
        return true;
    if (*m_mapName == NULL)
        return true;
    if (m_header == nullptr)
        return true;
    if (m_plane == nullptr)
        return true;
    if (m_node == nullptr)
        return true;
    if (m_leaf == nullptr)
        return true;

    return false;
}

wchar_t* ConvertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

bool BSPParser::Load(const char* path, const char* mapName)
{
    strcpy_s(m_path, sizeof m_path, path);
    strcpy_s(m_mapName, sizeof m_mapName, mapName);

    wchar_t* wPath = ConvertCharArrayToLPCWSTR(path);
    const HANDLE hFile = CreateFile(wPath, GENERIC_READ, NULL, nullptr, OPEN_ALWAYS, NULL, nullptr);
    if (hFile == nullptr)
    {
        return false;
    }

    const DWORD dwSize = GetFileSize(hFile, nullptr);
    if (!dwSize)
    {
        CloseHandle(hFile);
        return false;
    }

    m_data = new BYTE[dwSize];

    DWORD dwRead = NULL;
    if (!ReadFile(hFile, m_data, dwSize, &dwRead, nullptr))
    {
        CloseHandle(hFile);
        delete[] m_data;
        return false;
    }

    CloseHandle(hFile);

    m_header = (dheader_t*)m_data;

    m_node = (dnode_t*)(m_data + m_header->lumps[LUMP_NODES].fileofs);
    m_plane = (dplane_t*)(m_data + m_header->lumps[LUMP_PLANES].fileofs);
    m_leaf = (dleaf_t*)(m_data + m_header->lumps[LUMP_LEAVES].fileofs);

    return true;
}

void BSPParser::SetPath(const char* path)
{
    strcpy_s(m_path, sizeof m_path, path);
}

int BSPParser::GetVersion() const
{
    return m_header->version;
}

int BSPParser::GetRevision() const
{
    return m_header->mapRevision;
}

const char* BSPParser::GetPath() const
{
    return m_path;
}

const char* BSPParser::GetName() const
{
    return m_mapName;
}

dnode_t* BSPParser::GetNodeLump() const
{
    return m_node;
}

dleaf_t* BSPParser::GetLeafLump() const
{
    return m_leaf;
}

dplane_t* BSPParser::GetPlaneLump() const
{
    return m_plane;
}

dleaf_t* BSPParser::GetLeafFromPoint(Vector3 point)
{
    int nodeNum = 0;

    while (nodeNum >= 0)
    {
        if (&m_node == nullptr || &m_plane == nullptr)
            return nullptr;

        dnode_t* node = &m_node[nodeNum];
        dplane_t* plane = &m_plane[node->planenum];

        const float d = point.Dot(plane->normal) - plane->dist;
        if (d > 0)
            nodeNum = node->children[0];
        else
            nodeNum = node->children[1];
    }

    return &m_leaf[-nodeNum - 1];
}

// Ghetto approach
bool BSPParser::IsVisible(const Vector3 start, Vector3 end)
{
    // Map is null so doesn't even matter
    if (IsNull())
        return true;

    // Check if we're trying to read 
   if ((start.x < -4095) || (start.x > 4095) ||
        (start.y < -4095) || (start.y > 4095) ||
        (start.z < -4095) || (start.z > 4095))
    {
        std::cout << "TraceLine: Starting beyond the end of the world\n" << std::endl;
        return false;
    }

    // Clamp the end vector
    if (end.x > 4095.0f)
    {
        const float percent = 4095.0f / end.x;
        end.y = end.y * percent;
        end.z = end.z * percent;
        end.x = 4095.0f;
    }

    if (end.y > 4095.0f)
    {
        const float percent = 4095.0f / end.y;
        end.x = end.x * percent;
        end.z = end.z * percent;
        end.y = 4095.0f;
    }

    if (end.z > 4095.0f)
    {
        const float percent = 4095.0f / end.z;
        end.x = end.x * percent;
        end.y = end.y * percent;
        end.z = 4095.0f;
    }

    if (end.x < -4095.0f)
    {
        const float percent = 4095.0f / end.x;
        end.y = end.y * percent;
        end.z = end.z * percent;
        end.x = -4095.0f;
    }

    if (end.y < -4095.0f)
    {
        const float percent = 4095.0f / end.y;
        end.x = end.x * percent;
        end.z = end.z * percent;
        end.y = -4095.0f;
    }

    if (end.z < -4095.0f)
    {
        const float percent = 4095.0f / end.z;
        end.x = end.x * percent;
        end.y = end.y * percent;
        end.z = -4095.0f;
    }

    Vector3 direction = end - start;
    Vector3 point = start;

    int steps = int(direction.Length());

    // Stop if distance is too far or non-existent
    if (steps > 5000 || steps == 0)
        return false;

    direction /= float(steps);

    while (steps)
    {
        point += direction;
        dleaf_t* leaf = GetLeafFromPoint(point);

        if (leaf->contents & CONTENTS_SOLID)
            return false;

        --steps;
    }

    return true;
}
