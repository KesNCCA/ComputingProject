//Timer class with aspects learned from LazyFoo at https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php

#include "timer.h"

Timer::Timer() : m_ticks(0), m_Pticks(0), m_started(false), m_paused(false)
{
    //if the SDL subsystem timer isn't active then activate it.
    m_newStartPosition = 0;
    m_previousFrameTime = 0;

    if(SDL_WasInit(SDL_INIT_TIMER) == 0) SDL_InitSubSystem(SDL_INIT_TIMER);
}

Timer::~Timer(){}

void Timer::Start()
{
    m_started = true;
    m_paused = false;
    m_ticks = SDL_GetTicks();
}

void Timer::Reset()
{
    m_newStartPosition = m_DeltaTime;
}

void Timer::Pause()
{
    if(m_started == true)
    {
        m_paused = true;
        m_Pticks = SDL_GetTicks() - m_ticks;
    }
}

void Timer::Continue()
{
    if(m_started == true && m_paused == true)
    {
        m_paused = false;
        m_ticks = SDL_GetTicks() - m_Pticks;
    }
}

float Timer::DeltaTime()
{
    return m_DeltaTime;
}

float Timer::GetTime()
{
    if(m_started == true)
    {
        if(m_paused == true)
        {
            m_ElapsedTicks = m_Pticks;
            //To get value in seconds * 0.001f
            m_DeltaTime = m_ElapsedTicks * 0.001f;
        }
        else
            m_ElapsedTicks = SDL_GetTicks() - m_ticks;
        //To get value in seconds * 0.001f
        m_DeltaTime = m_ElapsedTicks * 0.001f;
    }
    return m_DeltaTime - m_newStartPosition;

}

float Timer::GetFPSDifference()
{
    float time = SDL_GetTicks() - m_previousFrameTime;
    m_previousFrameTime = SDL_GetTicks();

    return time;
}

