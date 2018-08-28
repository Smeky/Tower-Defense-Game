#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "string"
#include "map"

struct Tp_tower_stats {
    std::string name;
    std::string head_adrs;
    std::string desc_adrs;
};

struct Tp_enemy_stats {
    std::string name;
    std::string head_ards;
};

struct Tower_data {
    std::string name;
    std::string house;
    std::string tex_body;
    std::string tex_cannon;
    std::string tex_button;
    std::string tex_fire= "no_texture";
    std::string ability = "no_ability";
    std::string upgrade1 = "no_upgrade";
    std::string upgrade2 = "no_upgrade";
    std::string snd_attack = "no_sound";
    std::string projectName = "no_projectile";
    int dmg;
    int atts;
    int range;
    int price;
    int slowDur = 0;
    int freezeDur = 0;
    int blastRange = 0;
    float slowPwr = 0.0;
    float blastPwr = 0.0;
};

struct Enemy_data {
    std::string name;
    std::string type;
    std::string tex     = "no_texture";
    std::string snd_die = "no_sound";
    float health = 0;
    int speed    = 100;
    int price    = 0;
};

struct Projectile_data {
    std::string name;
    std::string tex = "no_texture";
    int width;
    int height;
    int vel;
    bool direction;
};

class ResourceManager {
public:
    bool init();
    void close();
    Tower_data getTowerData( std::string name );
    Enemy_data getEnemyData( std::string name );
    Projectile_data getProjectData( std::string name );
    Tp_tower_stats getTpTowerStats( std::string name );
    Tp_enemy_stats getTpEnemyStats( std::string name );
private:
    std::map<std::string,Tower_data>     m_towerData;
    std::map<std::string,Enemy_data>     m_enemyData;
    std::map<std::string,Projectile_data>m_projectileData;
    std::map<std::string,Tp_tower_stats> m_tpTowerStats;
    std::map<std::string,Tp_enemy_stats> m_tpEnemyStats;
};

#endif // RESOURCEMANAGER_H
