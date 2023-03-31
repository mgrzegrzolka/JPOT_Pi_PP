#include "jpotInstance.hpp"
#include  <stdlib.h> 
#include <map>

jpotInstance::jpotInstance(jpLvlSetting config) : id(config.id), name(config.name), mysteryValueMin(config.mysteryValueMin),
                                    mysteryValueMax(config.mysteryValueMax), minBet(config.minBet), restartValue(config.restartValue)
{
    hitPoint = calcHitPoint();
    jpValue = calcRestartValue();
}

void jpotInstance::increasingPot(uint bet)
{
    jpValue += bet;
}

uint  jpotInstance::calcHitPoint()
{
    uint range = mysteryValueMax - mysteryValueMin;
    
    if(range) {
        srand (time(NULL));
        return rand() % range + mysteryValueMin;
    }
    return 0;
}

uint jpotInstance::calcRestartValue()
{
    //now only fix restart value 
    return restartValue;
}

void jpotInstance::checkIfHit()
{
    
}