#ifndef _AKKLE_HPP_
#define _AKKLE_HPP_

#include <windows.h>

#define _WIN32_DCOM
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

#include <d3d9.h>
#include <d3dx9.h>

#include <math.h>

#include "ErrorHandler.hpp"

// Application Title
#define APP_TITLE L"Aki System Gague"

// Image Names
#define GAUGE_FACE L"Gauge.png"
#define GAUGE_NEEDLE L"Needle.png"
#define GAUGE_COVER L"Cover.png"

// Window Size
#define FULLSCREEN FALSE
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// Transparent Color
#define TRANS_COLOR D3DCOLOR_XRGB(255, 0, 255)

// Akkle tick rate
#define TICK_RATE 3000

class Gauge;

class Akkle
{
public:
    Akkle(HINSTANCE hInstance);
    ~Akkle();

    bool InitWindow(
                const wchar_t* lpWindowName,
                DWORD dwStyle,
                DWORD dwExStyle = 0,
                int x = CW_USEDEFAULT,
                int y = CW_USEDEFAULT,
                int nWidth = CW_USEDEFAULT,
                int nHeight = CW_USEDEFAULT,
                HWND hWndParent = 0,
                HMENU hMenu = 0
                );

    // Init first
    bool InitDirect3D(BOOL fullScreen);
    bool CleanDirect3D();

    // Init second
    bool InitProcessMonitor();
    bool CleanProcessMonitor();

    // Init third
    bool InitApp();
    bool CleanApp();

    // App Run functions
    bool Tick();
    bool Render();

    // D3D Device check
    bool GotDevice() { return m_gotDevice; }

    // D3D Device lost recovery
    bool RecoverDevice();

    HWND Window() { return m_hwnd; }

private:
    // App Data
    unsigned int m_lastTick;
    Gauge* m_gauge;
    LPD3DXSPRITE m_spriteHandler;
    DWORD m_cpuCount;

    // Process Monitor Data
    IWbemLocator* m_pLoc;
    IWbemServices* m_pSvc;
    double* m_lastCPUCheck;
    double* m_curCPUCheck;
    bool m_gotLastCheck;

    // Window Data
    HWND m_hwnd;
    HINSTANCE m_hInst;
    unsigned int m_screenWidth, m_screenHeight;

    // Direct3D Data
    D3DPRESENT_PARAMETERS m_d3dpp;
    LPDIRECT3D9 m_d3d;
    LPDIRECT3DDEVICE9 m_d3dDev;
    bool m_gotDevice;
    LPDIRECT3DSURFACE9 m_backBuffer;

private:
    const wchar_t* ClassName() const { return L"Akkle Class"; }
    WNDCLASSEX BuildClass();

    LPDIRECT3DSURFACE9 LoadSurface(wchar_t* fileName, D3DCOLOR transColor);
    LPDIRECT3DTEXTURE9 LoadTexture(wchar_t* fileName, D3DCOLOR transColor);

    bool GetProcessorInfo(double* checkVal);
};

#endif