#include "core/ResourceManager.h"
#include "core/tinyxml2.h"
using namespace tinyxml2;

#include "iostream"
using namespace std;

bool ResourceManager::init() {
    bool success = true;

    XMLDocument file;

    if( file.LoadFile( "media/data/resources.xml" ) != XML_NO_ERROR ) {
        cout << "Failed to load resources.xml file." << endl;
        success = false;
    }
    else {
        XMLElement* guiElement = file.FirstChildElement( "GUI" );

        if( guiElement == NULL ) {
            cout << "Top element <GUI> is missing." << endl;
            success = false;
        }
        else {
            XMLElement* tpsElement = guiElement->FirstChildElement( "tooltip" );

            if( tpsElement == NULL ) {
                cout << "There is no element <tooltip>. Game tooltips will not be displayed." << endl;
            }
            else {
                while( tpsElement != NULL ) {
                    string tpName = tpsElement->Attribute( "name" );
                    string tpType = tpsElement->Attribute( "type" );

                    if( tpType == "tower_statistic" ) {
                        m_tpTowerStats.insert( { tpName, Tp_tower_stats() } );

                        m_tpTowerStats[ tpName ].name       = tpName;
                        m_tpTowerStats[ tpName ].head_adrs  = tpsElement->FirstChildElement( "head" )->GetText();
                        m_tpTowerStats[ tpName ].desc_adrs  = tpsElement->FirstChildElement( "desc" )->GetText();
                    }
                    else if( tpType == "enemy_statistic" ) {
                        m_tpEnemyStats.insert( { tpName, Tp_enemy_stats() } );

                        m_tpEnemyStats[ tpName ].name       = tpName;
                        m_tpEnemyStats[ tpName ].head_ards  = tpsElement->FirstChildElement( "head" )->GetText();
                    }


                    tpsElement = tpsElement->NextSiblingElement( "tooltip" );
                }
            }
        }

        XMLElement* entityElement = file.FirstChildElement( "entities" );

        if( entityElement == NULL ) {
            cout << "Top element <entities> is missing." << endl;
            success = false;
        }
        else {
            XMLElement* towerElement = entityElement->FirstChildElement( "towers" )->FirstChildElement();

            if( towerElement == NULL ) {
                cout << "Tower level element is missing." << endl;
                return false;
            }
            else {
                while( towerElement != NULL ) {
                    string towerName = towerElement->Attribute( "name" );

                    m_towerData.insert( { towerName, Tower_data() } );

                    m_towerData[ towerName ].name       = towerName;
                    m_towerData[ towerName ].house      = towerElement->Attribute( "house" );

                    XMLElement* texElement = towerElement->FirstChildElement( "texture" );

                    if( texElement == NULL ) {
                        cout << "Texture element of " << towerName << " is missing." << endl;
                    }
                    else {
                        m_towerData[ towerName ].tex_body   = texElement->Attribute( "tex-body" );
                        m_towerData[ towerName ].tex_cannon = texElement->Attribute( "tex-cannon" );
                        m_towerData[ towerName ].tex_button = texElement->Attribute( "tex-button" );
                    }

                    XMLElement* prjElement = towerElement->FirstChildElement( "projectile" );

                    if( prjElement != NULL ) {
                        m_towerData[ towerName ].projectName = prjElement->Attribute( "name" );
                    }

                    XMLElement* sndElement = towerElement->FirstChildElement( "sound" );

                    if( sndElement != NULL ) {
                        m_towerData[ towerName ].snd_attack = sndElement->Attribute( "attack" );
                    }

                    XMLElement* statElement = towerElement->FirstChildElement( "stats" );

                    if( statElement == NULL ) {
                        cout << "Stats element of " << towerName << " is missing." << endl;
                        success = false;
                    }
                    else {
                        m_towerData[ towerName ].dmg    = statElement->IntAttribute( "dmg" );
                        m_towerData[ towerName ].atts   = statElement->IntAttribute( "atts" );
                        m_towerData[ towerName ].range  = statElement->IntAttribute( "range" );
                        m_towerData[ towerName ].price  = statElement->IntAttribute( "price" );
                    }

                    XMLElement* abiElement = towerElement->FirstChildElement( "ability" );

                    if( abiElement != NULL ) {
                        string abiName = abiElement->Attribute( "name" );

                        m_towerData[ towerName ].ability = abiName;

                        if( abiName == "slow" ) {
                            m_towerData[ towerName ].slowDur = abiElement->IntAttribute( "dur" );
                            m_towerData[ towerName ].slowPwr = abiElement->FloatAttribute( "prc" );
                        }
                        else if( abiName == "freeze" ) {
                            m_towerData[ towerName ].freezeDur = abiElement->IntAttribute( "dur" );
                        }
                        else if( abiName == "blast" ) {
                            m_towerData[ towerName ].blastPwr   = abiElement->FloatAttribute( "dmg" );
                            m_towerData[ towerName ].blastRange = abiElement->IntAttribute( "radius" );
                        }
                        else {
                            m_towerData[ towerName ].ability = "no_ability";
                        }
                    }

                    XMLElement* upgElement = towerElement->FirstChildElement( "upgrade" );

                    if( upgElement != NULL ) {
                        if( upgElement->Attribute( "first" ) != NULL ) {
                            m_towerData[ towerName ].upgrade1 = upgElement->Attribute( "first" );
                        }
                        if( upgElement->Attribute( "second" ) != NULL ) {
                            m_towerData[ towerName ].upgrade2 = upgElement->Attribute( "second" );
                        }
                    }

                    towerElement = towerElement->NextSiblingElement();
                }
            }

            XMLElement* enemyElement = entityElement->FirstChildElement( "enemies" )->FirstChildElement();

            if( enemyElement == NULL ) {
                cout << "Enemy element is missing." << endl;
                return false;
            }
            else {
                while( enemyElement != NULL ) {
                    string enemyName = enemyElement->Attribute( "name" );

                    m_enemyData.insert( { enemyName, Enemy_data() } );

                    m_enemyData[ enemyName ].name   = enemyName;
                    m_enemyData[ enemyName ].type   = enemyElement->Attribute( "type" );

                    XMLElement* texElement = enemyElement->FirstChildElement( "texture" );

                    if( texElement == NULL ) {
                        cout << "Texture element of " << enemyName << " is missing." << endl;
                    }
                    else {
                        m_enemyData[ enemyName ].tex    = texElement->Attribute( "tex" );
                    }

                    XMLElement* statElement = enemyElement->FirstChildElement( "stats" );

                    if( statElement == NULL ) {
                        cout << "Stat element of " << enemyName << " is missing." << endl;
                    }
                    else {
                        m_enemyData[ enemyName ].speed  = statElement->IntAttribute( "speed" );
                    }

                    enemyElement = enemyElement->NextSiblingElement();
                }
            }

            XMLElement* projectElement = entityElement->FirstChildElement( "projectiles" )->FirstChildElement();

            if( projectElement == NULL ) {
                cout << "Projectile element is missing." << endl;
                return false;
            }
            else {
                while( projectElement != NULL ) {
                    string projectName = projectElement->Attribute( "name" );

                    m_projectileData.insert( { projectName, Projectile_data() } );

                    m_projectileData[ projectName ].name    = projectName;
                    m_projectileData[ projectName ].tex     = projectElement->Attribute( "tex" );
                    m_projectileData[ projectName ].width   = projectElement->IntAttribute( "w" );
                    m_projectileData[ projectName ].height  = projectElement->IntAttribute( "h" );
                    m_projectileData[ projectName ].vel     = projectElement->IntAttribute( "vel" );
                    m_projectileData[ projectName ].direction = projectElement->IntAttribute( "direction" );

                    projectElement = projectElement->NextSiblingElement();
                }
            }
        }
    }

    return success;
}

void ResourceManager::close() {

}

Tower_data ResourceManager::getTowerData( std::string name ) {
    return m_towerData[ name ];
}

Enemy_data ResourceManager::getEnemyData( std::string name ) {
    return m_enemyData[ name ];
}

Projectile_data ResourceManager::getProjectData( std::string name ) {
    return m_projectileData[ name ];
}

Tp_tower_stats ResourceManager::getTpTowerStats( std::string name ) {
    return m_tpTowerStats[ name ];
}

Tp_enemy_stats ResourceManager::getTpEnemyStats( std::string name ) {
    return m_tpEnemyStats[ name ];
}
