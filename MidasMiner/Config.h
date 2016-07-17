//
//  Config.h
//  MidasMiner
//
//  Created by Ying Wang on 06/05/16.
//  Copyright © 2016 Ying. All rights reserved.
//

#ifndef Config_h
#define Config_h

#define LOG_DEBUG

#ifdef LOG_DEBUG
#  define D(x) printf("%s\n", x)
#else
#  define D(x) do {} while (0)
#endif

class Config{
public:
    static const int SCREEN_WIDTH = 755;
    static const int SCREEN_HEIGHT = 600;
    static const int X_OFFSET = 320;
    static const int Y_OFFSET = 100;
    static const int TEXT_X_OFFSET = 60;
    static const int TEXT_Y_OFFSET = 60;
    static const int TEXT_Y_GAP = 50;
};

#endif /* Config_h */
