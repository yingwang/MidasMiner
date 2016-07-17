//
//  Level.h
//  MidasMiner
//
//  Created by Ying Wang on 07/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Level_h
#define Level_h

#include <vector>
#include "Header.h"
#include "Diamond.h"

using namespace std;

class Level
{
private:
    int numOfRow = 8;
    int numOfCol = 8;
    vector<bool> map =
    {
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,
    };
    int time;
    int moves;
    
public:
    vector<bool> GetMap();
    int GetNumOfRow();
    int GetNumOfCol();
};

#endif /* Level_h */
