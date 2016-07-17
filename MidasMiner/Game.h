//
//  Game.h
//  MidasMiner
//
//  Created by Ying Wang on 06/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <vector>
#include <sstream>
#include "Header.h"
#include "Texture.h"
#include "Level.h"
#include "Diamond.h"
#include "DiamondTexture.h"
#include "Swap.h"
#include "Timer.h"
#include "TextTexture.h"
#include "Score.h"
#include "Music.h"

class Game
{
private:
    int numOfRow;
    int numOfCol;
    bool speedUp;
    Score score;
    Timer timer;
    Swap currentSwap;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* event;
    Music* music;
    Level* level;
    Diamond* diamonds[8][8];

    Texture* backgroundTexture;
    std::vector<Diamond*> diamondToRemove;
    std::vector<DiamondTexture*> diamondTexture;
    std::vector<TextTexture*> textTexture;

    void TrySwap();
    void Update();
    void DetectMatches();
    bool DetectDiamondChainVerticalAndHorizontal(int row, int col);
    void RollBack();
    void PerformSwap();
    void RemoveDiamondChain();
    void Refill();
    void FillHoles();
    void LoadMusic();
    void PlayMusic();
    void DetectAndRemoveAllDiamondChain();
    void AddNewDiamonds();
    void OnMouseButtonDown(int xPos, int yPos);
    void OnMouseButtonUp(int xPos, int yPos);
    void Init();
    void LoadTextures();
    void ShuffleDiamonds();
    void RenderTextures();
    void Close();
    void Input();
    void CheckTimer();
    
public:
    enum GameState {
        IDLE,
        TRYSWAP,
        ROLLBACK,
        SWAP,
        REFILL,
        END,
    };
    
    GameState currentGameState;
    static bool quitGame;
    Game();
    ~Game();

    void MainLoop();
};

#endif /* Game_h */
