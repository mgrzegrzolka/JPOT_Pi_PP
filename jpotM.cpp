#include "jpotM.hpp"
#include <map>
#include <utility>
#include <string>
#include "json.hpp"
#include <fstream>
#include "jpotInstance.hpp"

jpotM::jpotM()
{
    read_config_file();
}

bool jpotM::read_config_file()
{
    nlohmann::json config;
    jpLvlSetting tmpSetting;
    printf("Read config file !!!");
    
    std::ifstream sFile("settings.json");
    if(sFile) {
        try {
            config = nlohmann::json::parse(sFile);
        }
        catch (nlohmann::json::parse_error& ex) {
            printf("Parse error at byte %lu", ex.byte);
            return false;
        }
        for(nlohmann::json& el : config["jp_lvl_config"]) {
            tmpSetting.id = el["id"].get<int>();
            tmpSetting.name = el["name"].get<std::string>();
            tmpSetting.mysteryValueMin = el["mysteryValueMin"].get<int>();
            tmpSetting.mysteryValueMax = el["mysteryValueMax"].get<int>();
            tmpSetting.minBet = el["minBet"].get<int>();
            tmpSetting.restartValue = el["restartValue"].get<int>();

            main_settings.push_back(tmpSetting);
        }

        return true;
    }
    return false;
}

bool jpotM::start_jp_cycle()
{
    printf("Start jp cycle");

    while(true) {
        printf("Get input from EGM");
        int bet = 50;
        std::string egm = "EGM1";
        increasingAllPot(bet, egm);
        checkAllJpHits();
        sendAllWin();
    }
    create_jp_instance(main_settings);
    return true;
}

bool jpotM::create_jp_instance(std::vector<jpLvlSetting> main_s)
{
    printf("Create instance");
    int iId;
    for(auto &e: main_s) {
        auto instTmp = instances.find(e.id);
        iId = 0;
        if(instTmp == instances.end()) {
            instances.insert(std::make_pair(e.id, new jpotInstance(e, iId)));
        } else if(instTmp->second->getStatus() > 1) {
            iId = instTmp->second->getInstId();
            delete instTmp->second; // del current completed instance 
            instTmp->second = new jpotInstance(e, iId); // create new instace
        }
    }
    return true;
}

void jpotM::increasingAllPot(uint bet, std::string egmId)
{
    for(auto inst = instances.begin(); inst != instances.end(); ++inst) {
        inst->second->increasingPot(bet, egmId);
    }
}

int jpotM::checkAllJpHits()
{
    int noofHit = 0;
    for(auto inst = instances.begin(); inst != instances.end(); ++inst) {
        if(inst->second->checkIfHit()) noofHit++;
    }
    return noofHit;
}

void jpotM::sendAllWin()
{
    /* send win to egm */
}