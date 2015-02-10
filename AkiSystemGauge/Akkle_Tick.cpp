#include "Akkle.hpp"
#include "Gauge.hpp"

#define TICK_FREQ 30

bool Akkle::Tick()
{
    // Make sure the Direct3D device is valid
    if (m_d3dDev == NULL)
        return false;

    if ((GetTickCount() - m_lastTick) >= TICK_RATE)
    {
        m_lastTick = GetTickCount();

        if (!GetProcessorInfo(m_curCPUCheck))
            return false;

        if ((m_curCPUCheck[1] - m_lastCPUCheck[1]) > 0)
        {
            m_gauge[0].Tick(1.0 - (m_curCPUCheck[0] - m_lastCPUCheck[0]) / (m_curCPUCheck[1] - m_lastCPUCheck[1]));
        }
        else
        {
            HandleErrorMsg("Divide by zero for CPU check", "Error", DEFAULT_ERROR, m_hwnd);
            return false;
        }

        if ((m_curCPUCheck[3] - m_lastCPUCheck[3]) > 0)
        {
            m_gauge[1].Tick(1.0 - (m_curCPUCheck[2] - m_lastCPUCheck[2]) / (m_curCPUCheck[3] - m_lastCPUCheck[3]));
        }
        else
        {
            HandleErrorMsg("Divide by zero for CPU check", "Error", DEFAULT_ERROR, m_hwnd);
            return false;
        }

        int x = 0;
        for (unsigned int i = 0; i < m_cpuCount; i++)
        {
            if ((m_curCPUCheck[x + 1] - m_lastCPUCheck[x + 1]) > 0)
            {
                m_gauge[i].Tick(1.0 - (m_curCPUCheck[x] - m_lastCPUCheck[x]) / (m_curCPUCheck[x + 1] - m_lastCPUCheck[x + 1]));
            }
            else
            {
                HandleErrorMsg("Divide by zero for CPU check", "Error", DEFAULT_ERROR, m_hwnd);
                return false;
            }

            x += 2;
        }

        m_gotLastCheck = false;
    }
    else if (!m_gotLastCheck)
    {
        if (!GetProcessorInfo(m_lastCPUCheck))
            return false;
        m_gotLastCheck = true;
    }

    return true;
}