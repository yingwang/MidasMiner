//
//  Music.cpp
//  MidasMiner
//
//  Created by Ying Wang on 09/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include "Music.h"

Music::Music()
{
    finishPlayed = false;
}

Music::~Music()
{
    Mix_FreeChunk(chunkMatch);
    Mix_FreeChunk(chunkNoMatch);
    Mix_FreeChunk(chunkFinish);
    Mix_FreeMusic(backGroundMusicSlow);
    Mix_FreeMusic(backGroundMusicFast);
    chunkMatch = nullptr;
    chunkNoMatch = nullptr;
    chunkFinish = nullptr;
    backGroundMusicSlow = nullptr;
    backGroundMusicFast = nullptr;
}

void Music::LoadMusic()
{
    backGroundMusicSlow = Mix_LoadMUS("Resources/overworld.wav");
    backGroundMusicFast = Mix_LoadMUS("Resources/overworldfast.wav");
    chunkFinish = Mix_LoadWAV("Resources/levelend.wav");
    chunkMatch = Mix_LoadWAV("Resources/oneup.wav");
    chunkNoMatch = Mix_LoadWAV("Resources/blockhit.wav");
}

void Music::PlayBackGroundMusicSlow()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(backGroundMusicSlow, -1);
    }
}

void Music::PlayBackGroundMusicFast()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(backGroundMusicFast, -1);
    }
}

void Music::PauseBackGroundMusic()
{
    Mix_PauseMusic();
}

void Music::StopBackGroundMusic()
{
    Mix_HaltMusic();
}

void Music::PlayMatchSound()
{
    Mix_PlayChannel(-1, chunkMatch, 0);
}

void Music::PlayNoMatchSound()
{
    Mix_PlayChannel(-1, chunkNoMatch, 0);
}

void Music::PlayFinishSound()
{
    if (finishPlayed) return;
    finishPlayed = true;
    Mix_PlayChannel(-1, chunkFinish, 0);
}
