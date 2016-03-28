
#include "Timer.h"

void Timer::start()
{
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
}

void Timer::stop()
{
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
}

double Timer::elapsedMilliseconds()
{
    std::chrono::time_point<std::chrono::system_clock> endTime;
    
    if(m_bRunning)
    {
        endTime = std::chrono::system_clock::now();
    }
    else
    {
        endTime = m_EndTime;
    }
    
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

double Timer::elapsedSeconds()
{
    return elapsedMilliseconds() / 1000.0;
}

FPSCounter::FPSCounter()
{
    m_Timer.start();
}

bool FPSCounter::update()
{
    m_FrameCount++;
    
    if(m_Timer.elapsedMilliseconds() >= m_RefreshRate)
    {
        m_CurrentFPS = static_cast<double>(m_FrameCount) / m_Timer.elapsedSeconds();
        
        m_FrameCount = 0;
        m_Timer.start();
        
        return true;
    }
    
    return false;
}
