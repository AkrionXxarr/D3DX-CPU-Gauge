#include "Gauge.hpp"

bool Gauge::Tick(double cpuPercent = 0)
{
    m_needleLastProjRot = m_needleProjRot;
    m_needleProjRot = (cpuPercent * m_rotMax) + m_rotOffset;
    //m_needleProjRot = m_rotMax + m_rotOffset;

    m_rotPadding = ROTATION_PADDING;

    return true;
}