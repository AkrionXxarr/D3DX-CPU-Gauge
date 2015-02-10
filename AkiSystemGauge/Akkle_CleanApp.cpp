#include "Akkle.hpp"
#include "Gauge.hpp"

bool Akkle::CleanApp()
{
    m_gauge->Clean();

    return true;
}