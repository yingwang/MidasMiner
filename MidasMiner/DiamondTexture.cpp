//
//  DiamondTexture.cpp
//  MidasMiner
//
//  Created by Ying Wang on 08/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include "DiamondTexture.h"

using namespace std;

DiamondTexture::DiamondTexture(SDL_Renderer* r, const string& path, const string& name): Texture(r, path, name)
{
}

void DiamondTexture::Draw(int x, int y)
{
    SDL_Rect renderQuad = {x, y, SHAPE_WIDTH, SHAPE_HEIGHT};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

int DiamondTexture::GetTotalWidth()
{
    return  SHAPE_WIDTH + MARGIN;
}

int DiamondTexture::GetTotalHeight()
{
    return  SHAPE_HEIGHT + MARGIN;
}
