#ifndef __jpotInstance__
#define __jpotInstance__

#include "common.hpp"
#include <string>

class jpotInstance
{
public:
    jpotInstance(jpLvlSetting config);
    ~jpotInstance() {};

    uint calcHitPoint();
    uint calcRestartValue();
    void increasingPot(uint bet);
    void checkIfHit();
private:
    int id;
    std::string name;
    uint hitPoint;
    uint jpValue;
    uint mysteryValueMin;
    uint mysteryValueMax;
    uint minBet;
    uint restartValue;
};

#endif