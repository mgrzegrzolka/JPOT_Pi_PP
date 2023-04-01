#ifndef __jpotM__
#define __jpotM__

#include <map>
#include <string>
#include "json.hpp"
#include "common.hpp"
#include "jpotInstance.hpp"

class jpotM
{
public:
    jpotM();
    ~jpotM() {};

    bool read_config_file();
    bool start_jp_cycle();
    bool create_jp_instance(std::vector<jpLvlSetting> main_s);
private:
    void increasingAllPot(uint bet, std::string egmId);
    int checkAllJpHits();
    void sendAllWin();
    std::vector<jpLvlSetting> main_settings;
    std::map<int, jpotInstance*> instances; 
};

#endif /* jpotM */