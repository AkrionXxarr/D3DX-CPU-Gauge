#include "Akkle.hpp"

bool Akkle::RecoverDevice()
{
    HRESULT hResult;

    hResult = m_d3dDev->Reset(&m_d3dpp);

    switch (hResult)
    {
    case D3D_OK:
        m_gotDevice = true;
        HandleErrorMsg("D3D_OK", "Error", DEFAULT_ERROR, m_hwnd);
        break;

    case D3DERR_DEVICELOST:
        m_gotDevice = false;
        HandleErrorMsg("D3DERR_DEVICELOST", "Error", DEFAULT_ERROR, m_hwnd);
        break;

    case D3DERR_DEVICEREMOVED:
        HandleErrorMsg("D3DERR_DEVICEREMOVED", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
        break;

    case D3DERR_DRIVERINTERNALERROR:
        HandleErrorMsg("D3DERR_DRIVERINTERNALERROR", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
        break;
        
    case D3DERR_OUTOFVIDEOMEMORY:
        HandleErrorMsg("D3DERR_OUTOFVIDEOMEMORY", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
        break;

    default:
        // Seems to be D3DERR_INVALIDCALL
        HandleErrorMsg("Default", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
        break;
    }

    /*
    if (hResult == D3DERR_DEVICELOST)
        m_gotDevice = false;
    else if (hResult == D3D_OK)
        m_gotDevice = true;
    else
        return false;
        */

    return true;
}