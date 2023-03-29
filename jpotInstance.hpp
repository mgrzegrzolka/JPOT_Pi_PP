#ifndef __jpotInstance__
#define __jpotInstance__

#include "common.hpp"
#include <string>

class jpotInstance
{
public:
    jpotInstance(jpLvlSetting config) : id(config.id), name(config.name), mysteryValueMin(config.mysteryValueMin),
                                        mysteryValueMax(config.mysteryValueMax), minBet(config.minBet), restartValue(config.restartValue)
    {
        //TODO
    };
    ~jpotInstance() {};

    void increasing_pot(int bet);
private:
    int id;
    std::string name;
    int mysteryValueMin;
    int mysteryValueMax;
    int minBet;
    int restartValue;
};

#endif