//
//  TextTexture.h
//  MidasMiner
//
//  Created by Ying Wang on 09/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef TextTexture_h
#define TextTexture_h

#include "Header.h"
#include "Texture.h"

using namespace std;

class TextTexture : Texture
{
private:
    int width;
    int height;
    TTF_Font* font;
    SDL_Color textColor = {255, 255, 255, 255};
    int xOffset;
    int yOffset;
public:
    TextTexture(SDL_Renderer* r, const string& path, const string& name, const string& textToRender);
    ~TextTexture();
    void Draw(int x, int y);
    void Update(const string& textToRender);
};

#endif /* TextTexture_h */
