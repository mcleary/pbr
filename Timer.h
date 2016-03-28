#pragma once

#include <chrono>

class Timer
{
public:
    void start();
    void stop();
    
    double elapsedMilliseconds();
    double elapsedSeconds();
    
private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

class FPSCounter
{
public:
    FPSCounter();
    
    bool update();
    
    double getFPS()
    {
        return m_CurrentFPS;
    }
    
    void setRefreshRate(double refreshRate)
    {
        m_RefreshRate = refreshRate;
    }
    
private:
    Timer m_Timer;
    
    double m_RefreshRate   = 1000;
    int    m_FrameCount    = 0;
    double m_CurrentFPS    = 0;
};