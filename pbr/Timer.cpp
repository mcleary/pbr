
#include "Timer.h"

using namespace std::chrono;
using namespace std::chrono_literals;

Timer::Timer()
{
    Start();
}

void Timer::Start()
{
    m_StartTime = Clock::now();
    m_bRunning = true;
}

void Timer::Stop()
{
    m_EndTime = Clock::now();
    m_bRunning = false;
}

Timer::Duration Timer::Elapsed() 
{
	TimePoint EndTime;

	if (m_bRunning)
	{
		EndTime = Clock::now();
	}
	else
	{
		EndTime = m_EndTime;
	}

	return EndTime - m_StartTime;
}

float Timer::ElapsedMilliseconds()
{
	return static_cast<float>(duration_cast<FloatMilliseconds>(Elapsed()).count());
}

float Timer::ElapsedSeconds()
{	
	return static_cast<float>(duration_cast<FloatSeconds>(Elapsed()).count());
}

FPSTimer::FPSTimer() :
    Timer()
{
	m_RefreshRate = 1s;
}

bool FPSTimer::Update()
{
    m_FrameCount++;
    
    if(Elapsed() >= m_RefreshRate)
    {
        m_CurrentFPS = static_cast<float>(m_FrameCount) / ElapsedSeconds();        
        m_FrameCount = 0;
        Start();
        
        return true;
    }
    
    return false;
}

float FPSTimer::GetFPS()
{
	return m_CurrentFPS;
}
