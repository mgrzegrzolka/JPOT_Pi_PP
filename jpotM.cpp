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
        for(auto inst = instances.begin(); inst != instances.end(); ++inst) {
            inst->second->increasing_pot(bet);
        }
    }
    create_jp_instance(main_settings);
    return true;
}

bool jpotM::create_jp_instance(std::vector<jpLvlSetting> main_s)
{
    printf("Create instance");
    for(auto &e: main_s) {
        if(instances.find(e.id) == instances.end()) {
            instances.insert(std::make_pair(e.id,new jpotInstance(e)));
        }
    }
    return true;
}
