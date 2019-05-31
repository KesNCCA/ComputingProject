#ifndef TIMER_H
#define TIMER_H
#include <SDL.h>
#include <iostream>

class Timer
{

public:

    Timer();
    ~Timer();

    bool Started();

    bool Paused();

    void Start();

    void Pause();

    void Continue();

    void Reset();

    float DeltaTime();

    float GetTime();

    float GetFPS();

    float GetFPSDifference();

private:

    //unsigned float mStartTicks;
    float CountedFrames;

    float Framerate;

    float mElapsedTicks;

    float mDeltaTime;

    float ticks;
    float Pticks;

    float newStartPosition;

    float previousFrameTime;

    bool started;
    bool paused;

};

#endif // TIMER_H
