//
//  Swap.cpp
//  MidasMiner
//
//  Created by Ying Wang on 08/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include "Swap.h"

Swap::Swap()
{
    ResetSwap();
}

Swap::~Swap()
{
    fromRow = -1;
    fromCol = -1;
    toRow = -1;
    toCol = -1;
    fromDiamond = NULL;
    toDiamond = NULL;
    validSwap = false;
}

void Swap::SetFromRow(int r)
{
    fromRow = r;
}

int Swap::GetFromRow()
{
    return fromRow;
}

void Swap::SetFromCol(int c)
{
    toCol = c;
}

int Swap::GetFromCol()
{
    return fromCol;
}

void Swap::SetToRow(int r)
{
    toRow = r;
}

int Swap::GetToRow()
{
    return toRow;
}

void Swap::SetToCol(int c)
{
    toCol = c;
}

int Swap::GetToCol()
{
    return toCol;
}

void Swap::SetFromLocation(int x, int y)
{
    fromRow = (y - Config::Y_OFFSET)/DiamondTexture::GetTotalHeight();
    fromCol = (x - Config::X_OFFSET)/DiamondTexture::GetTotalWidth();
}

void Swap::SetToLocation(int x, int y)
{
    toRow = (y - Config::Y_OFFSET)/DiamondTexture::GetTotalHeight();
    toCol = (x - Config::X_OFFSET)/DiamondTexture::GetTotalWidth();
    if ((fromRow == toRow) && (fromCol == toCol))
    {
        return;
    }
    ValidateSwap();
}

void Swap::ValidateSwap()
{
    if ((fromRow < 0)||(fromRow > 7)||(fromCol < 0)||(fromCol > 7))
    {
        ResetSwap();
        return;
    }
    if ((toRow < 0)||(toRow > 7)||(toCol < 0)||(toCol > 7))
    {
        ResetSwap();
        return;
    }
    if ((fromRow == toRow) && (fromCol == toCol))
    {
        ResetSwap();
        return;
    }
    if ((abs(fromCol - toCol) + abs(fromRow - toRow)) != 1)
    {
        ResetSwap();
        return;
    }
    validSwap = true;
}

bool Swap::GetValidSwap()
{
    return validSwap;
}

void Swap::ResetValidSwap()
{
    validSwap = false;
}

void Swap::ResetSwap()
{
    fromRow = -1;
    fromCol = -1;
    toRow = -1;
    toCol = -1;
    fromDiamond = NULL;
    toDiamond = NULL;
    validSwap = false;
}

void Swap::SetFromDiamond(Diamond* d)
{
    fromDiamond = d;
}

void Swap::SetToDiamond(Diamond* d)
{
    toDiamond = d;
}

Diamond* Swap::GetFromDiamond()
{
    return fromDiamond;
}

Diamond* Swap::GetToDiamond()
{
    return toDiamond;
}

