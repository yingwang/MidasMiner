//
//  Timer.cpp
//  MidasMiner
//
//  Created by Ying Wang on 09/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include <sstream>
#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    
    started = false;
    paused = false;
    
    timeOut = false;
    timeOutSoon = false;
}

void Timer::Start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::Stop()
{
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::Pause()
{
    if (started && !paused)
    {
        paused = true;
        
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::Unpause()
{
    if (started && paused)
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Timer::GetTicks()
{
    Uint32 time = 0;
    if (started)
    {
        if (paused)
        {
            time = pausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}

bool Timer::Started()
{
    return started;
}

bool Timer::Paused()
{
    return paused;
}

std::string Timer::GetRemainingTime()
{
    int remainingTime = (60 - GetTicks() / 1000);
    if (remainingTime <= 0)
    {
        remainingTime = 0;
        Pause();
        timeOut = true;
    }
    else if (remainingTime <= 15)
    {
        timeOutSoon = true;
    }
    std::stringstream timeText;
    timeText<<remainingTime;
    return timeText.str();
}

bool Timer::GetTimeOut()
{
    return timeOut;
}

bool Timer::GetTimeOutSoon()
{
    return timeOutSoon;
}