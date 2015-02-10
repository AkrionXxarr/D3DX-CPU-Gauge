#include "Akkle.hpp"
#include "Gauge.hpp"

bool Akkle::Render()
{
    HRESULT hResult;

    // Start rendering
    if (m_d3dDev->BeginScene())
    {
        m_d3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

        m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

        for (unsigned int i = 0; i < m_cpuCount; i++)
        {
            m_gauge[i].Draw(m_d3dDev, m_spriteHandler, m_backBuffer);
        }
        m_spriteHandler->End();

        // Stop Rendering
        m_d3dDev->EndScene();
    }

    // Display the back buffer on the screen
    hResult = m_d3dDev->Present(NULL, NULL, NULL, NULL);
    if (hResult == D3DERR_DEVICELOST)
    {
        m_gotDevice = false;
        HandleErrorMsg("Device lost", "Error - Debug", DEFAULT_ERROR, m_hwnd);
    }

    return true;
}