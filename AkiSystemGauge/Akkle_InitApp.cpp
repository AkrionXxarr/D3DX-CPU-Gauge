#include "Akkle.hpp"
#include "Gauge.hpp"

bool Akkle::InitApp()
{
    HRESULT hResult;
    LPDIRECT3DTEXTURE9 texture;

    D3DXIMAGE_INFO needleInfo;
    D3DXIMAGE_INFO faceInfo;
    D3DXIMAGE_INFO coverInfo;

    int gaugeCol = 0, gaugeRow= 0;
    int xOffset = 0, yOffset = 0;

    // Get number of logical CPUs
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    m_cpuCount = sysInfo.dwNumberOfProcessors;

    m_lastCPUCheck = new double [(m_cpuCount + 1) * 2];
    m_curCPUCheck = new double [(m_cpuCount + 1) * 2];

    // Initialize m_*CPUCheck variables
    if (!GetProcessorInfo(m_lastCPUCheck))
        return false;
    m_gotLastCheck = true;

    // Initialize sprite handler
    hResult = D3DXCreateSprite(m_d3dDev, &m_spriteHandler);
    if (hResult != D3D_OK)
        return false;

    m_gauge = new Gauge[m_cpuCount];

    gaugeCol = (m_cpuCount + (m_cpuCount % 2)) / 2;

    if (gaugeCol == 0)
    {
        HandleErrorMsg("Akkle::InitApp() | Divide by zero catch", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    gaugeRow = (m_cpuCount + (m_cpuCount % 2)) / gaugeCol;

    unsigned int i = 0;

    hResult = D3DXGetImageInfoFromFile(GAUGE_FACE, &faceInfo);
    if (hResult != D3D_OK)
        return false;
    hResult = D3DXGetImageInfoFromFile(GAUGE_NEEDLE, &needleInfo);
    if (hResult != D3D_OK)
        return false;
    hResult = D3DXGetImageInfoFromFile(GAUGE_COVER, &coverInfo);
    if (hResult != D3D_OK)
        return false;

    for (int row = 0; row < gaugeRow; row++)
    {
        xOffset = 0;
        for (int col = 0; col < gaugeCol; col++)
        {
            if (i >= m_cpuCount)
                break;

            texture = LoadTexture(GAUGE_FACE, TRANS_COLOR);
            m_gauge[i].SetFace(texture, faceInfo.Width, faceInfo.Height);

            texture = LoadTexture(GAUGE_NEEDLE, TRANS_COLOR);
            m_gauge[i].SetNeedle(texture, needleInfo.Width, needleInfo.Height);

            texture = LoadTexture(GAUGE_COVER, TRANS_COLOR);
            m_gauge[i].SetCover(texture, coverInfo.Width, coverInfo.Height);

            m_gauge[i].Offset(xOffset, yOffset);

            xOffset += faceInfo.Width;

            i++;
        }
        yOffset += faceInfo.Height;
    }

    return true;
}