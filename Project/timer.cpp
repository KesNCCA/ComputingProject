//Timer class with aspects learned from LazyFoo at https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php

#include "timer.h"

Timer::Timer() : ticks(0), Pticks(0), started(false), paused(false)
{
    //if the SDL subsystem timer isn't active then activate it.
    newStartPosition = 0;
    previousFrameTime = 0;

    if(SDL_WasInit(SDL_INIT_TIMER) == 0) SDL_InitSubSystem(SDL_INIT_TIMER);
}

Timer::~Timer(){}

void Timer::Start()
{
    started = true;
    paused = false;
    ticks = SDL_GetTicks();
}

void Timer::Reset()
{
    newStartPosition = mDeltaTime;
}

void Timer::Pause()
{
    if(started == true)
    {
        paused = true;
        Pticks = SDL_GetTicks() - ticks;
    }
}

void Timer::Continue()
{
    if(started == true && paused == true)
    {
        paused = false;
        ticks = SDL_GetTicks() - Pticks;
    }
}

float Timer::DeltaTime()
{
    return mDeltaTime;
}

float Timer::GetTime()
{
    if(started == true)
    {
        if(paused == true)
        {
            mElapsedTicks = Pticks;
            //To get value in seconds * 0.001f
            mDeltaTime = mElapsedTicks * 0.001f;
        }
        else
            mElapsedTicks = SDL_GetTicks() - ticks;
        //To get value in seconds * 0.001f
        mDeltaTime = mElapsedTicks * 0.001f;
    }
    return mDeltaTime - newStartPosition;

}

float Timer::GetFPSDifference()
{
    float time = SDL_GetTicks() - previousFrameTime;
    previousFrameTime = SDL_GetTicks();

    return time;
}

