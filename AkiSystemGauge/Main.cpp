#include "Akkle.hpp"

int WINAPI WinMain(
                HINSTANCE hInstance, 
                HINSTANCE hPrevInstance,
                LPSTR lpCmdLine,
                int nCmdShow)
{
    MSG msg = { 0 };
    Akkle akkle(hInstance);

    D3DXIMAGE_INFO faceInfo;
    SYSTEM_INFO sysInfo;
    unsigned int cpuCount;
    unsigned int screenWidth, screenHeight;
    unsigned int gaugeCol, gaugeRow;
    HRESULT hResult;

    hResult = D3DXGetImageInfoFromFile(GAUGE_FACE, &faceInfo);
    if (hResult != D3D_OK)
        return 0;
    GetSystemInfo(&sysInfo);

    cpuCount = sysInfo.dwNumberOfProcessors;

    gaugeCol = (cpuCount + (cpuCount % 2)) / 2;

    if (gaugeCol == 0)
    {
        HandleErrorMsg("Main() | Divide by zero catch", "Error", DEFAULT_ERROR, NULL);
        return false;
    }

    gaugeRow = (cpuCount + (cpuCount % 2)) / gaugeCol;

    screenWidth = faceInfo.Width * gaugeCol;
    screenHeight = faceInfo.Height * gaugeRow;

    // Create Window
    if (!akkle.InitWindow(APP_TITLE, (WS_CAPTION | WS_SYSMENU), 0, CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight))
    {
        HandleErrorMsg("InitWindow failed", "Error", DEFAULT_ERROR, NULL);
        return 0;
    }

    // Show window
    ShowWindow(akkle.Window(), nCmdShow);
    UpdateWindow(akkle.Window());

    // Initialize Direct 3D
    if (!akkle.InitDirect3D(FULLSCREEN))
    {
        HandleErrorMsg("InitDirect3D failed", "Error", DEFAULT_ERROR, NULL);
        return 0;
    }

    // Initialize Process Monitor
    if (!akkle.InitProcessMonitor())
    {
        HandleErrorMsg("InitProcessMonitor failed", "Error", DEFAULT_ERROR, NULL);
        akkle.CleanProcessMonitor();
    }

    // Initialize App
    if (!akkle.InitApp())
    {
        HandleErrorMsg("InitApp failed", "Error", DEFAULT_ERROR, NULL);
        return 0;
    }

    bool done = false;

    while (!done)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Look for quit message
            if (msg.message == WM_QUIT)
                done = true;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (akkle.GotDevice())
            {
                if (!akkle.Tick())
                {
                    HandleErrorMsg("Akkle::Tick() returned false", "Error!", DEFAULT_ERROR, akkle.Window());
                    done = true;
                }
                if (!akkle.Render())
                {
                    HandleErrorMsg("Akkle::Render() returned false", "Error!", DEFAULT_ERROR, akkle.Window());
                    done = true;
                }
            }
            else
            {
                if (!akkle.RecoverDevice())
                {
                    HandleErrorMsg("Akkle::RecoverDevice() returned false", "Error!", DEFAULT_ERROR, akkle.Window());
                    done = true;
                }
            }
        }
    }

    return msg.wParam;
}