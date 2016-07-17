//
//  Score.h
//  MidasMiner
//
//  Created by Ying Wang on 09/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Score_h
#define Score_h

using namespace std;

class Score
{
private:
    int currentScore;
public:
    Score();
    void Increase(int numOfDiamondToRemove);
    string GetScore();
    string GetRanking();
};

#endif /* Score_h */
