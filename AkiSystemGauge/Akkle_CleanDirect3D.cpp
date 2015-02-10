#include "Akkle.hpp"

bool Akkle::CleanDirect3D()
{
    if (m_d3dDev != NULL)
    {
        m_d3dDev->Release();
        m_d3dDev = NULL;
    }

    if (m_d3d != NULL)
    {
        m_d3d->Release();
        m_d3d = NULL;
    }

    return true;
}