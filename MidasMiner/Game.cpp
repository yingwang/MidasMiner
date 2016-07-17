 //
//  Game.cpp
//  MidasMiner
//
//  Created by Ying Wang on 06/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include "Game.h"

bool Game::quitGame = false;

Game::Game()
{
    Game::quitGame = false;
    currentGameState = GameState::IDLE;
}

Game::~Game()
{
}

void Game::Init()
{
    int ret;
    ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
    assert(ret >= 0);
    window = SDL_CreateWindow("Midas Miner - Ying Wang", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    assert(window != NULL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer != NULL);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    ret = IMG_Init(imgFlags) & imgFlags;
    assert(ret);
    ret = TTF_Init();
    assert(ret != -1);
    ret = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    assert(ret >= 0);
}

void Game::LoadTextures()
{
    backgroundTexture = new Texture(renderer, "Resources","BackGround.jpg");
    diamondTexture.push_back(new DiamondTexture(renderer, "Resources", "Blue.png"));
    diamondTexture.push_back(new DiamondTexture(renderer, "Resources", "Green.png"));
    diamondTexture.push_back(new DiamondTexture(renderer, "Resources", "Purple.png"));
    diamondTexture.push_back(new DiamondTexture(renderer, "Resources", "Red.png"));
    diamondTexture.push_back(new DiamondTexture(renderer, "Resources", "Yellow.png"));
    textTexture.push_back(new TextTexture(renderer, "Resources", "FreeMonoBold.ttf", "Time"));
    textTexture.push_back(new TextTexture(renderer, "Resources", "FreeMonoBold.ttf", "60"));
    textTexture.push_back(new TextTexture(renderer, "Resources", "FreeMonoBold.ttf", "Score"));
    textTexture.push_back(new TextTexture(renderer, "Resources", "FreeMonoBold.ttf", "0"));
    textTexture.push_back(new TextTexture(renderer, "Resources", "FreeMonoBold.ttf", "Congratulations!"));
}

void Game::ShuffleDiamonds()
{
    level = new Level();
    srand((unsigned int)time(NULL));
    Diamond::Color color;
    numOfRow = level->GetNumOfRow();
    numOfCol = level->GetNumOfCol();
    for (int row = 0; row < numOfRow; row++)
    {
        for (int col = 0; col < numOfCol; col++ )
        {
            if (level->GetMap()[row * numOfCol + col])
            {
                do
                {
                    color = Diamond::Color(rand() % 5 + 1);
                }
                while (((row >= 2)&&(color == diamonds[row - 1][col]->GetColor())&&(color == diamonds[row - 2][col]->GetColor()))||
                         ((col >= 2)&&(color == diamonds[row][col - 1]->GetColor())&&(color == diamonds[row][col - 2]->GetColor())));
                diamonds[row][col] = new Diamond(color);
                diamonds[row][col]->SetRow(row);
                diamonds[row][col]->SetCol(col);
            }
            else
            {
                // No diamond in this position
                diamonds[row][col] = new Diamond(Diamond::NONE);
            }
        }
    }
}

void Game::RenderTextures()
{
    backgroundTexture->Draw();
    
    for (int i = 0; i < textTexture.size() - 1; i++)
    {
        textTexture[i]->Draw(Config::TEXT_X_OFFSET, Config::TEXT_Y_OFFSET + Config::TEXT_Y_GAP * i);
    }
    
    int diamondWidth = DiamondTexture::GetTotalWidth();
    int diamondHeight = DiamondTexture::GetTotalHeight();
    for (int row = 0; row < numOfRow; row++)
    {
        for (int col = 0; col < numOfCol; col++ )
        {
            if ((diamonds[row][col] == NULL) || (diamonds[row][col]->GetColor() == Diamond::NONE)) {
                continue;
            }
            diamondTexture[diamonds[row][col]->GetColor() - 1]->Draw(Config::X_OFFSET + diamondWidth * col, Config::Y_OFFSET + diamondHeight * row);
        }
    }
    
    textTexture[1]->Update(timer.GetRemainingTime().c_str());
    textTexture[3]->Update(score.GetScore().c_str());
    if (timer.GetTimeOut())
    {
        textTexture[4]->Draw(0, 0);
        textTexture[4]->Update(score.GetRanking().c_str());
    }
}

void Game::CheckTimer()
{
    if (timer.GetTimeOut() && (currentGameState == GameState::IDLE))
    {
        currentGameState = GameState::END;
    }
}

void Game::Close()
{
    for (int row = 0; row < numOfRow; row++)
    {
        for (int col = 0; col < numOfCol; col++)
        {
            delete diamonds[row][col];
            diamonds[row][col] = NULL;
        }
    }
    
    delete  backgroundTexture;
    backgroundTexture = NULL;
    for (int i = 0; i < diamondToRemove.size(); i++)
    {
        delete diamondToRemove[i];
        diamondToRemove[i] = NULL;
    }
    for (int i = 0; i < diamondTexture.size(); i++)
    {
        delete diamondTexture[i];
        diamondTexture[i] = NULL;
    }
    for (int i = 0; i < textTexture.size(); i++)
    {
        delete textTexture[i];
        textTexture[i] = NULL;
    }
    
    delete level;
    delete event;
    delete music;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    level = NULL;
    event = NULL;
    music = NULL;
    window = NULL;
    renderer = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::LoadMusic()
{
    music = new class Music();
    music->LoadMusic();
    speedUp = false;
    music->PlayBackGroundMusicSlow();
}

void Game::PlayMusic()
{
    if (timer.GetTimeOut())
    {
        music->PauseBackGroundMusic();
        music->PlayFinishSound();
    }
    else if ((timer.GetTimeOutSoon()) && (!speedUp))
    {
        speedUp = true;
        music->StopBackGroundMusic();
        music->PlayBackGroundMusicFast();
    }
}

void Game::FillHoles()
{
    for (int row = numOfRow - 1; row > 0; row--)
    {
        for (int col = numOfCol - 1; col >= 0; col--)
        {
            if (diamonds[row][col] == NULL)
            {
                for (int up = row - 1; up >= 0; up--)
                {
                    if ((diamonds[up][col] != NULL) && (diamonds[up][col]->GetColor() != Diamond::NONE))
                    {
                        diamonds[row][col] = diamonds[up][col];
                        diamonds[row][col]->SetRow(row);
                        diamonds[up][col] = NULL;
                        break;
                    }
                }
            }
        }
    }
}

void Game::AddNewDiamonds()
{
    srand((unsigned int)time(NULL));
    bool filled = false;
    Diamond::Color color;
    for (int row = 0; row < numOfRow; row++)
    {
        filled = true;
        for (int col = 0; col < numOfCol; col++)
        {
            if (diamonds[row][col] == NULL)
            {
                filled = false;
                do
                {
                    color = Diamond::Color(rand() % 5 + 1);
                }
                while (((row >= 2)&&(color == diamonds[row - 1][col]->GetColor())&&(color == diamonds[row - 2][col]->GetColor()))||
                         ((col >= 2)&&(color == diamonds[row][col - 1]->GetColor())&&(color == diamonds[row][col - 2]->GetColor())));
                diamonds[row][col] = new Diamond(color);
                diamonds[row][col]->SetRow(row);
                diamonds[row][col]->SetCol(col);
            }
        }
        if (filled) break;
    }
}

void Game::DetectAndRemoveAllDiamondChain()
{
    bool hasDiamondChain = true;
    while (hasDiamondChain)
    {
        hasDiamondChain = false;
        for (int row = numOfRow - 1; row >= 0; row--)
        {
            for (int col = numOfCol - 1; col >= 0; col--)
            {
                if (DetectDiamondChainVerticalAndHorizontal(row, col))
                {
                    hasDiamondChain = true;
                    RemoveDiamondChain();
                    FillHoles();
                    AddNewDiamonds();
                }
            }
        }
    }
}

void Game::Refill()
{
    FillHoles();
    AddNewDiamonds();
    DetectAndRemoveAllDiamondChain();
    currentGameState = GameState::IDLE;
    if (timer.GetTimeOut()) currentGameState = GameState::END;
}

void Game::PerformSwap()
{
    RemoveDiamondChain();
    currentSwap.ResetSwap();
    currentGameState = GameState::REFILL;
}

void Game::RemoveDiamondChain()
{
    for (int i = 0; i < diamondToRemove.size(); i++)
    {
        int row = diamondToRemove[i]->GetRow();
        int col = diamondToRemove[i]->GetCol();
        if ((row >= 0) && (row < numOfRow) && (col >=0 ) && (col < numOfCol))
        {
            if (diamonds[row][col] != NULL)
            {
                delete diamonds[row][col];
                diamonds[row][col] = NULL;
            }
        }
    }
    diamondToRemove.clear();
}

void Game::RollBack()
{
    diamonds[currentSwap.GetFromRow()][currentSwap.GetFromCol()] = currentSwap.GetFromDiamond();
    diamonds[currentSwap.GetFromRow()][currentSwap.GetFromCol()]->SetRow(currentSwap.GetToRow());
    diamonds[currentSwap.GetFromRow()][currentSwap.GetFromCol()]->SetCol(currentSwap.GetToCol());
    diamonds[currentSwap.GetToRow()][currentSwap.GetToCol()]= currentSwap.GetToDiamond();
    diamonds[currentSwap.GetToRow()][currentSwap.GetToCol()]->SetRow(currentSwap.GetFromRow());
    diamonds[currentSwap.GetToRow()][currentSwap.GetToCol()]->SetCol(currentSwap.GetFromCol());
    
    currentSwap.ResetSwap();
    currentGameState = GameState::IDLE;
    if (timer.GetTimeOut()) currentGameState = GameState::END;
}

void Game::TrySwap()
{
    diamonds[currentSwap.GetFromRow()][currentSwap.GetFromCol()] = currentSwap.GetToDiamond();
    diamonds[currentSwap.GetFromRow()][currentSwap.GetFromCol()]->SetRow(currentSwap.GetFromRow());
    diamonds[currentSwap.GetFromRow()][currentSwap.GetFromCol()]->SetCol(currentSwap.GetFromCol());
    diamonds[currentSwap.GetToRow()][currentSwap.GetToCol()]= currentSwap.GetFromDiamond();
    diamonds[currentSwap.GetToRow()][currentSwap.GetToCol()]->SetRow(currentSwap.GetToRow());
    diamonds[currentSwap.GetToRow()][currentSwap.GetToCol()]->SetCol(currentSwap.GetToCol());
    currentGameState = GameState::TRYSWAP;
}

void Game::DetectMatches()
{
    Diamond* from = currentSwap.GetFromDiamond();
    Diamond* to = currentSwap.GetToDiamond();
    
    if ((from->GetColor() == Diamond::NONE) || (to->GetColor() == Diamond::NONE))
    {
        currentGameState = GameState::ROLLBACK;
        return;
    }
    
    if (DetectDiamondChainVerticalAndHorizontal(from->GetRow(), from->GetCol())
            | DetectDiamondChainVerticalAndHorizontal(to->GetRow(), to->GetCol()))
    {
        music->PlayMatchSound();
        currentGameState = GameState::SWAP;
        score.Increase((int)diamondToRemove.size());
    }
    else
    {
        music->PlayNoMatchSound();
        currentGameState = GameState::ROLLBACK;
    }
}

bool Game::DetectDiamondChainVerticalAndHorizontal(int row, int col)
{
    bool match = false;
    int diamondColor = diamonds[row][col]->GetColor();
    
    // Detect Vertical Matches
    int vertLength = 1;
    for (int i = row - 1; i >= 0; i--)
    {
        if (diamonds[i][col]->GetColor() == diamondColor)
        {
            vertLength++;
            diamondToRemove.push_back(diamonds[i][col]);
        }
        else
        {
            break;
        }
    }
    for (int i = row + 1; i < numOfRow; i++)
    {
        if (diamonds[i][col]->GetColor() == diamondColor)
        {
            vertLength++;
            diamondToRemove.push_back(diamonds[i][col]);
        }
        else
        {
            break;
        }
    }
    if (vertLength < 3)
    {
        diamondToRemove.erase(diamondToRemove.end() - vertLength + 1, diamondToRemove.end());
    }
    
    // Detect Horizontal Matches
    int HorizLength = 1;
    for (int i = col - 1; i >= 0; i--)
    {
        if (diamonds[row][i]->GetColor() == diamondColor)
        {
            HorizLength++;
            diamondToRemove.push_back(diamonds[row][i]);
        }
        else
        {
            break;
        }
    }
    for (int i = col + 1; i < numOfCol && diamonds[row][i]->GetColor() == diamondColor; i++)
    {
        if (diamonds[row][i]->GetColor() == diamondColor)
        {
            HorizLength++;
            diamondToRemove.push_back(diamonds[row][i]);
        }
        else
        {
            break;
        }
    }
    if (HorizLength < 3)
    {
        diamondToRemove.erase(diamondToRemove.end() - HorizLength + 1, diamondToRemove.end());
    }
    
    if ((vertLength >= 3) || (HorizLength >= 3))
    {
        match = true;
        diamondToRemove.push_back(diamonds[row][col]);
    }
    return match;
}

void Game::OnMouseButtonDown(int xPos, int yPos)
{
    if (currentSwap.GetFromRow() < 0)
    {
        currentSwap.SetFromLocation(xPos, yPos);
    }
}

void Game::OnMouseButtonUp(int xPos, int yPos)
{
    currentSwap.SetToLocation(xPos, yPos);
    
    if (currentSwap.GetValidSwap())
    {
        currentSwap.SetFromDiamond(diamonds[currentSwap.GetFromRow()][currentSwap.GetFromCol()]);
        currentSwap.SetToDiamond(diamonds[currentSwap.GetToRow()][currentSwap.GetToCol()]);
        TrySwap();
        currentSwap.ResetValidSwap();
    }
}

void Game::Input()
{
    int xPos, yPos;
    switch (event->type) {
        case SDL_QUIT:
            quitGame = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (timer.GetTimeOut())
            {
                break;
            }
            SDL_GetMouseState(&xPos, &yPos);
            OnMouseButtonDown(xPos, yPos);
            break;
        case SDL_MOUSEBUTTONUP:
            if (timer.GetTimeOut())
            {
                break;
            }
            SDL_GetMouseState(&xPos, &yPos);
            OnMouseButtonUp(xPos, yPos);
            break;
        default:
            break;
    }
}

void Game::Update()
{
    switch (currentGameState) {
        case GameState::IDLE:
            Input();
            break;
        case GameState::TRYSWAP:
            DetectMatches();
            break;
        case GameState::ROLLBACK:
            RollBack();
            break;
        case GameState::SWAP:
            PerformSwap();
            break;
        case GameState::REFILL:
            Refill();
            break;
        case GameState::END:
            Input();
            break;
        default:
            break;
    }
}

void Game::MainLoop()
{
    Init();
    event = new SDL_Event();
    LoadTextures();
    LoadMusic();
    ShuffleDiamonds();
    timer.Start();
    while(!quitGame)
    {
        while(SDL_PollEvent(event) != 0)
        {
            SDL_RenderClear(renderer);
            Update();
            PlayMusic();
            RenderTextures();
            CheckTimer();
            SDL_RenderPresent(renderer);
        }
    }
    Close();
}




