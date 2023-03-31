#ifndef __common__
#define __common__

#include <string>

struct jpLvlSetting{
    int id;
    std::string name;
    uint mysteryValueMin;
    uint mysteryValueMax;
    uint minBet;
    uint restartValue;
};

#endif