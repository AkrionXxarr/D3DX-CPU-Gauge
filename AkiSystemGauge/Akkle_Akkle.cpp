#include "Akkle.hpp"
#include "Gauge.hpp"

Akkle::Akkle(HINSTANCE hInstance)
{
    // App Data
    m_gauge = NULL;
    m_cpuCount = 0;
    m_spriteHandler = NULL;
    m_lastTick = GetTickCount();

    // Process Monitor Data
    m_pLoc = NULL;
    m_pSvc = NULL;
    m_lastCPUCheck = NULL;
    m_curCPUCheck = NULL;
    m_gotLastCheck = false;

    // Window Data
    m_hwnd = NULL;
    m_hInst = hInstance;
    m_screenWidth = 0;
    m_screenHeight = 0;

    // Direct3D Data
    ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
    m_d3d = NULL;
    m_d3dDev = NULL;
    m_gotDevice = false;
    m_backBuffer = NULL;
}

Akkle::~Akkle()
{
    delete [] m_gauge;
    delete [] m_lastCPUCheck;
    delete [] m_curCPUCheck;
}