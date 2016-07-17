//
//  Music.h
//  MidasMiner
//
//  Created by Ying Wang on 09/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Music_h
#define Music_h

#include "Header.h"

class Music
{
private:
    Mix_Music* backGroundMusicSlow = nullptr;
    Mix_Music* backGroundMusicFast = nullptr;
    Mix_Chunk* chunkFinish = nullptr;
    Mix_Chunk* chunkMatch = nullptr;
    Mix_Chunk* chunkNoMatch = nullptr;
    bool finishPlayed;
public:
    Music();
    ~Music();
    void LoadMusic();
    void PlayMatchSound();
    void PlayNoMatchSound();
    void PlayFinishSound();
    void PlayBackGroundMusicSlow();
    void PlayBackGroundMusicFast();
    void PauseBackGroundMusic();
    void StopBackGroundMusic();
    Mix_Music* GetBackGroundMusicSlow();
    Mix_Music* GetBackGroundMusicFast();
};

#endif /* Music_h */
