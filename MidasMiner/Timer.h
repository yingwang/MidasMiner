//
//  Timer.h
//  MidasMiner
//
//  Created by Ying Wang on 09/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

#include "Header.h"

class Timer
{
private:
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool paused;
    bool started;
    bool timeOutSoon;
    bool timeOut;
    
public:
    Timer();
    void Start();
    void Stop();
    void Pause();
    void Unpause();
    Uint32 GetTicks();
    bool Started();
    bool Paused();
    bool GetTimeOut();
    bool GetTimeOutSoon();
    std::string GetRemainingTime();
};

#endif /* Timer_h */
