//
//  Diamond.h
//  MidasMiner
//
//  Created by Ying Wang on 07/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Diamond_h
#define Diamond_h

#include "Texture.h"

class Diamond
{
private:
    int color;
    int row;
    int col;
    
public:
    enum Color {NONE, BLUE, GREEN, PURPLE, RED, YELLOW};
    Diamond(Diamond::Color c);
    int GetColor();
    int GetRow();
    int GetCol();
    void SetRow(int r);
    void SetCol(int c);
    void SetColor(int clr);
};

#endif /* Diamond_h */
