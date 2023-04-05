#ifndef __jpotInstance__
#define __jpotInstance__

#include "common.hpp"
#include <string>
#include <stack>
#include <utility>

class jpotInstance
{
public:
    jpotInstance(common::jpLvlSetting config, int prevId);
    ~jpotInstance() {};

    uint calcHitPoint();
    uint calcRestartValue();
    void increasingPot(uint bet, std::string egmId);
    bool checkIfHit();
    int getStatus();
    int getInstId();
    void printInstaceState();
    void sendWin();
private:
    int id;
    int instId;
    std::string name;
    uint hitPoint;
    uint jpValue;
    uint mysteryValueMin;
    uint mysteryValueMax;
    uint minBet;
    uint restartValue;
    std::stack<std::pair<std::string, uint>> contributeList;
    int status; /* 0 - active, 1 - after hit */
};

#endif