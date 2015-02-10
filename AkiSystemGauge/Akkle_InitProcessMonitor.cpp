#include "Akkle.hpp"

bool Akkle::InitProcessMonitor()
{
    HRESULT hResult;

    // Initialize COM
    hResult = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hResult))
    {
        HandleErrorMsg("CoInitializeEx failed.", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    // Set COM security levels
    hResult = CoInitializeSecurity(
                        NULL,
                        -1,
                        NULL,
                        NULL,
                        RPC_C_AUTHN_LEVEL_DEFAULT,
                        RPC_C_IMP_LEVEL_IMPERSONATE,
                        NULL,
                        EOAC_NONE,
                        NULL
                        );
    if (FAILED(hResult))
    {
        HandleErrorMsg("CoInitializeSecurity failed.", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    // Obtain the initial locator to WMI
    hResult = CoCreateInstance(
                            CLSID_WbemLocator,
                            0,
                            CLSCTX_INPROC_SERVER,
                            IID_IWbemLocator,
                            (LPVOID*) &m_pLoc
                            );
    if (FAILED(hResult))
    {
        HandleErrorMsg("CoCreateInstance failed.", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    // Connect to WMI through the IWbemLocator::ConnectServer method:
    hResult = m_pLoc->ConnectServer(
                                _bstr_t(L"ROOT\\CIMV2"),
                                NULL,
                                NULL,
                                0,
                                NULL,
                                0,
                                0,
                                &m_pSvc
                                );
    if (FAILED(hResult))
    {
        HandleErrorMsg("ConnectServer failed.", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    // Set security levels on the proxy
    hResult = CoSetProxyBlanket(
                    m_pSvc,
                    RPC_C_AUTHN_WINNT,
                    RPC_C_AUTHZ_NONE,
                    NULL,
                    RPC_C_AUTHN_LEVEL_CALL,
                    RPC_C_IMP_LEVEL_IMPERSONATE,
                    NULL,
                    EOAC_NONE
                    );
    if (FAILED(hResult))
    {
        HandleErrorMsg("CoSetProxyBlanket failed.", "Error", DEFAULT_ERROR, m_hwnd);
        return false;
    }

    return true;
}