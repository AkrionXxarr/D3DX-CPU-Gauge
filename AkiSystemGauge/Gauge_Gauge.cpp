#include "Gauge.hpp"

Gauge::Gauge()
{
    m_face = NULL;
    m_needle = NULL;
    m_cover = NULL;

    m_xOffset = 0; m_yOffset = 0;

    m_rotOffset = ROTATION_OFFSET;
    m_rotMax = ROTATION_MAX;

    m_needleProjRot = ROTATION_OFFSET;
    m_needleLastProjRot = ROTATION_OFFSET;
    m_needleCurRot = ROTATION_OFFSET;
    m_needleLastRot = 0;

    m_rotateStep = 0.0;
    m_needleStep = 0;

    m_curDelta = 0.0;
    m_lastDelta = 0.0;

    m_rotPow = 0.0;
    m_rotPadding = 0.0;

    m_lastTick = GetTickCount();
    m_tickRotDelay = 0;
    m_curRotDelay = ROTATION_DELAY;

    m_faceWidth = 0; m_faceHeight = 0;
    m_needleWidth = 0; m_needleHeight = 0;
    m_coverWidth = 0; m_coverHeight = 0;
}

Gauge::~Gauge()
{
}