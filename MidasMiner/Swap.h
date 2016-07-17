//
//  Swap.h
//  MidasMiner
//
//  Created by Ying Wang on 08/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Swap_h
#define Swap_h

#include "Config.h"
#include "DiamondTexture.h"
#include "Diamond.h"

class Swap
{
private:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    bool validSwap;
    Diamond* fromDiamond;
    Diamond* toDiamond;
    
    void ValidateSwap();
    
public:
    Swap();
    ~Swap();
    
    void SetFromRow(int r);
    int GetFromRow();
    void SetFromCol(int c);
    int GetFromCol();
    void SetToRow(int r);
    int GetToRow();
    void SetToCol(int c);
    int GetToCol();
    
    void SetFromLocation(int x, int y);
    void SetToLocation(int x, int y);
    void ResetSwap();
    bool GetValidSwap();
    void ResetValidSwap();
    
    void SetFromDiamond(Diamond* d);
    void SetToDiamond(Diamond* d);
    Diamond* GetFromDiamond();
    Diamond* GetToDiamond();
};

#endif /* Swap_h */
