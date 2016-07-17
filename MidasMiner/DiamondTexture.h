//
//  DiamondTexture.h
//  MidasMiner
//
//  Created by Ying Wang on 08/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef DiamondTexture_h
#define DiamondTexture_h

#include "Header.h"
#include "Texture.h"

using namespace std;

class DiamondTexture : public Texture
{
private:
    static const int SHAPE_WIDTH = 35;
    static const int SHAPE_HEIGHT = 35;
    static const int MARGIN = 10;
    
public:
    DiamondTexture(SDL_Renderer* r, const string& path, const string& name);
    void Draw(int x, int y);
    static int GetTotalWidth();
    static int GetTotalHeight();
};

#endif /* DiamondTexture_h */
