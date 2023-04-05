#include "jpotInstance.hpp"
#include  <stdlib.h> 
#include <map>

jpotInstance::jpotInstance(common::jpLvlSetting config, int prevId) : id(config.id), name(config.name), mysteryValueMin(config.mysteryValueMin),
                                    mysteryValueMax(config.mysteryValueMax), minBet(config.minBet), restartValue(config.restartValue), status(0)
{
    instId = (!prevId) ? 1 : prevId++;
    hitPoint = calcHitPoint();
    jpValue = calcRestartValue();
}

void jpotInstance::increasingPot(uint bet, std::string egmId)
{
    jpValue += bet;
    contributeList.push(make_pair(egmId, bet));
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

bool jpotInstance::checkIfHit()
{
    if(jpValue >= hitPoint) {
        status = 1;
        return true;
    }
    return false;
}

int jpotInstance::getStatus()
{
    return status;
}

int jpotInstance::getInstId() 
{
    return instId;
}

void jpotInstance::sendWin()
{
    printf("!!!!WIN!!!!! --- Id: %d, Inst: %d, Name: %s, Value: %d\n", id, instId, name.c_str(), jpValue);
    printf("!!!!EGM!!!!! --- EGM:%s \n-------------\n", contributeList.top().first.c_str());
    if(true) {
        status = 2;
    }
}
void jpotInstance::printInstaceState()
{
    printf("ID: %d, Inst: %d, Name: %s, JpValue: %d \n", id, instId, name.c_str(), jpValue);
}