//
//  Texture.h
//  MidasMiner
//
//  Created by Ying Wang on 06/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <string>
#include "Header.h"

using namespace std;

class Texture
{
private:
protected:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
public:
    Texture();
    Texture(SDL_Renderer* r, const string& path, const string& name);
    ~Texture();
    
    bool LoadFromFile(const string& path, const string& name);
    
    void Free();
    void Draw();

    void SetRenderer(SDL_Renderer* renderer);
    SDL_Renderer* GetRenderer();
};

#endif /* Texture_h */
