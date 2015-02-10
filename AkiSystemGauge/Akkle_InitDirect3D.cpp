#include "Akkle.hpp"

bool Akkle::InitDirect3D(BOOL fullScreen)
{
    // Initialize Direct3D
    m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (m_d3d == NULL)
    {
        HandleErrorMsg("Error initializing Direct3D", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    // Set Direct3D presentation parameters
    m_d3dpp.Windowed = (!fullScreen);
    m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    m_d3dpp.BackBufferCount = 1;
    m_d3dpp.BackBufferWidth = m_screenWidth;
    m_d3dpp.BackBufferHeight = m_screenHeight;
    m_d3dpp.hDeviceWindow = m_hwnd;

    // Create Direct3D device
    m_d3d->CreateDevice(
                    D3DADAPTER_DEFAULT,
                    D3DDEVTYPE_HAL,
                    m_hwnd,
                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                    &m_d3dpp,
                    &m_d3dDev
                    );

    if (m_d3dDev == NULL)
    {
        HandleErrorMsg("Error creating Direct3D device", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }
    else
    {
        m_gotDevice = true;
    }


    // Clear the backbuffer to black
    m_d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    // Create pointer to the back buffer
    m_d3dDev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer);

    return true;
}