//
//  Level.cpp
//  MidasMiner
//
//  Created by Ying Wang on 07/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include "Level.h"

std::vector<bool> Level::GetMap()
{
    return map;
}

int Level::GetNumOfRow()
{
    return numOfRow;
}

int Level::GetNumOfCol()
{
    return numOfCol;
}