#include "Gauge.hpp"

bool Gauge::Clean()
{
    if (m_face != NULL)
        m_face->Release();

    if (m_needle != NULL)
        m_needle->Release();

    if (m_cover != NULL)
        m_cover->Release();

    return true;
}