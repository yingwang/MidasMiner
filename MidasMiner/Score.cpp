//
//  Score.cpp
//  MidasMiner
//
//  Created by Ying Wang on 09/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#include <sstream>
#include "Score.h"

using namespace std;

Score::Score()
{
    currentScore = 0;
}

void Score::Increase(int numOfDiamondToRemove)
{
    if (numOfDiamondToRemove <= 3)
    {
        currentScore += 10;
    }
    else if (numOfDiamondToRemove <= 4)
    {
        currentScore += 30;
    }
    else if (numOfDiamondToRemove <= 5)
    {
        currentScore += 90;
    }
    else if (numOfDiamondToRemove <= 6)
    {
        currentScore += 300;
    }
    else
    {
        currentScore += 900;
    }
}

string Score::GetScore()
{
    std::stringstream scoreText;
    scoreText<<currentScore;
    return scoreText.str();
}

string Score::GetRanking()
{
    std::string per;
    if (currentScore > 15000)
    {
        per = "99";
    }
    else if (currentScore > 10000)
    {
        per = "97";
    }
    else if (currentScore > 8000)
    {
        per = "95";
    }
    else if (currentScore > 5000)
    {
        per = "90";
    }
    else if (currentScore > 2000)
    {
        per = "70";
    }
    else if (currentScore > 1000)
    {
        per = "50";
    }
    else if (currentScore > 500)
    {
        per = "30";
    }
    else if (currentScore > 100)
    {
        per = "10";
    }
    else
    {
        per = "0";
    }
    
    if (currentScore > 1000)
    {
        return (("Fabulous! You beat " + per + "% monsters in the Kingdom!"));
    }
    else
    {
        return (("Good Job! You beat " + per + "% monsters in the Kingdom!"));
    }
}