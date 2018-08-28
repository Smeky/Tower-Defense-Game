#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "vector"
#include "string"

struct Setting_data {
    unsigned int res_w;
    unsigned int res_h;
    bool vsync;
};

struct Level_data {
    std::string path;
    unsigned int id;
    bool unlocked;
    bool defeated;
};

struct Talent_data {
    unsigned int id;
    unsigned int amount;
};

class SaveManager {
public:
    bool init();
    bool saveSettings();
    bool saveGame();
    bool saveTalents();

    std::vector<Level_data>* getLevelData() { return &m_lvData; }
    Level_data*     getLevelData    ( unsigned int id ) { return &m_lvData[ id ]; }
    Talent_data*    getTalentData   ( unsigned int id ) { return &m_tlData[ id ]; }
    Setting_data*   getSaveData     () { return &m_svData; }

    int m_exp;
    int m_pLv;
private:
    std::vector<Level_data>     m_lvData;
    std::vector<Talent_data>    m_tlData;

    Setting_data    m_svData;
};

#endif // SAVEMANAGER_H
