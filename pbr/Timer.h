#pragma once

#include <chrono>

class Timer
{
public:
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration = TimePoint::duration;
	using FloatSeconds = std::chrono::duration<float, std::chrono::seconds::period>;
	using FloatMilliseconds = std::chrono::duration<float, std::chrono::milliseconds::period>;

    explicit Timer();

    void Start();
    void Stop();

	Duration Elapsed();    
    float ElapsedMilliseconds();
	float ElapsedSeconds();
    
private:
    TimePoint m_StartTime;
    TimePoint m_EndTime;
    bool      m_bRunning = false;
};

class FPSTimer : public Timer
{
public:
	FPSTimer();
    
    bool Update();
    
	float GetFPS();
    
    void SetRefreshRate(std::chrono::milliseconds RefreshRate)
    {
        m_RefreshRate = RefreshRate;
    }
    
private:    
	std::chrono::milliseconds m_RefreshRate;
	int   m_FrameCount = 0;
	float m_CurrentFPS = 0;
};