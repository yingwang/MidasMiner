//
//  Diamond.cpp
//  MidasMiner
//
//  Created by Ying Wang on 07/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include "Diamond.h"

Diamond::Diamond(Diamond::Color c)
{
    color = c;
}

int Diamond::GetColor()
{
    return color;
}

int Diamond::GetRow()
{
    return row;
}

int Diamond::GetCol()
{
    return col;
}

void Diamond::SetRow(int r)
{
    row = r;
}

void Diamond::SetCol(int c)
{
    col = c;
}

void Diamond::SetColor(int clr)
{
    color = clr;
}