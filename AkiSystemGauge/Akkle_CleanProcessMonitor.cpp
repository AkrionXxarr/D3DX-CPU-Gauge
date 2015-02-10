#include "Akkle.hpp"

bool Akkle::CleanProcessMonitor()
{
    if (m_pLoc != NULL)
        m_pLoc->Release();

    if (m_pSvc != NULL)
        m_pSvc->Release();

    CoUninitialize();

    return true;
}