#include "TooltipDescription.h"

#include "iostream"
using namespace std;

enum tpType {
    TP_TOWER_STAT,
    TP_ENEMY_STAT,
};

TooltipDescription::TooltipDescription( Engine* game, Tower_data data, int x, int y ) {
    m_towerData  = data;
    m_towerStats = game->Resources().getTpTowerStats( m_towerData.name );

    m_towerDmgAdrs = "TEMP_TP_TOWER_STAT_DMG";
    m_towerRngAdrs = "TEMP_TP_TOWER_STAT_RNG";
    m_towerAtsAdrs = "TEMP_TP_TOWER_STAT_ATS";
    m_towerPrcAdrs = "TEMP_TP_TOWER_STAT_PRC";

    game->createText( m_towerDmgAdrs, game->intToString( m_towerData.dmg ),     game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 240, 70 } );
    game->createText( m_towerRngAdrs, game->intToString( m_towerData.range ),   game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 240, 70 } );
    game->createText( m_towerAtsAdrs, game->intToString( m_towerData.atts ),    game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 240, 70 } );
    game->createText( m_towerPrcAdrs, game->intToString( m_towerData.price ),   game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 240, 70 } );

    m_box.w = 200;
    m_box.h = 160;
    m_box.x = x - m_box.w;
    m_box.y = y - m_box.h / 2;

    if( m_box.x < 5 ) {
        m_box.x = 5;
    }
    else if( m_box.x + m_box.w > game->getWindowW() - 5 ) {
        m_box.x = game->getWindowW() - m_box.w - 5;
    }

    if( m_box.y < 5 ) {
        m_box.y = 5;
    }
    else if( m_box.y + m_box.h > game->getWindowH() - 5 ) {
        m_box.y = game->getWindowH() - m_box.h - 5;
    }

    m_type = TP_TOWER_STAT;
}

TooltipDescription::TooltipDescription( Engine* game, Enemy_data data, int x, int y ) {
    m_enemyData  = data;
    m_enemyStats = game->Resources().getTpEnemyStats( m_enemyData.name );

    m_enemyHpsAdrs = "TEMP_TP_ENEMY_STAT_HPS";
    m_enemyWthAdrs = "TEMP_TP_ENEMY_STAT_WTH";
    m_enemySpdAdrs = "TEMP_TP_ENEMY_STAT_SPD";

    game->createText( m_enemyHpsAdrs, game->intToString( m_enemyData.health ),  game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 240, 70 } );
    game->createText( m_enemyWthAdrs, game->intToString( m_enemyData.price ),   game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 240, 70 } );
    game->createText( m_enemySpdAdrs, game->intToString( m_enemyData.speed ),   game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 240, 70 } );

    m_box.w = 160;
    m_box.h = 110;
    m_box.x = x - m_box.w;
    m_box.y = y - m_box.h / 2;

    if( m_box.x < 5 ) {
        m_box.x = 5;
    }
    else if( m_box.x + m_box.w > game->getWindowW() - 5 ) {
        m_box.x = game->getWindowW() - m_box.w - 5;
    }

    if( m_box.y < 5 ) {
        m_box.y = 5;
    }
    else if( m_box.y + m_box.h > game->getWindowH() - 5 ) {
        m_box.y = game->getWindowH() - m_box.h - 5;
    }

    m_type = TP_ENEMY_STAT;
}

void TooltipDescription::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 20, 20, 20, 235 );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    SDL_SetRenderDrawColor( game->getRenderer(), 0, 0, 0, 150 );
    SDL_RenderDrawRect( game->getRenderer(), &m_box );

    SDL_SetRenderDrawColor( game->getRenderer(), 160, 160, 160, 140 );
    SDL_RenderDrawLine( game->getRenderer(), m_box.x + 20, m_box.y + 30, m_box.x + m_box.w - 20, m_box.y + 30 );

    switch( m_type ) {
    case TP_TOWER_STAT:
        game->drawTexture( m_towerStats.head_adrs,          m_box.x + m_box.w / 2,  m_box.y + 15,       NULL, NULL, true,  true );
        game->drawTexture( "TEXT_TOOLTIP_TOWER_STATS_DMG",  m_box.x + 8,  m_box.y + m_box.h / 2 - 30,   NULL, NULL, false, true );
        game->drawTexture( "TEXT_TOOLTIP_TOWER_STATS_RNG",  m_box.x + 8,  m_box.y + m_box.h / 2 - 10,   NULL, NULL, false, true );
        game->drawTexture( "TEXT_TOOLTIP_TOWER_STATS_ATS",  m_box.x + 8,  m_box.y + m_box.h / 2 + 10,   NULL, NULL, false, true );
        game->drawTexture( "TEXT_TOOLTIP_TOWER_STATS_PRC",  m_box.x + 8,  m_box.y + m_box.h / 2 + 30,   NULL, NULL, false, true );
        game->drawTexture( m_towerDmgAdrs,                  m_box.x + 80, m_box.y + m_box.h / 2 - 30,   NULL, NULL, false, true );
        game->drawTexture( m_towerRngAdrs,                  m_box.x + 80, m_box.y + m_box.h / 2 - 10,   NULL, NULL, false, true );
        game->drawTexture( m_towerAtsAdrs,                  m_box.x + 80, m_box.y + m_box.h / 2 + 10,   NULL, NULL, false, true );
        game->drawTexture( m_towerPrcAdrs,                  m_box.x + 80, m_box.y + m_box.h / 2 + 30,   NULL, NULL, false, true );
        game->drawTexture( m_towerStats.desc_adrs,          m_box.x + 8,  m_box.y + m_box.h - 15,       NULL, NULL, false, true );
        break;
    case TP_ENEMY_STAT:
        game->drawTexture( m_enemyStats.head_ards,          m_box.x + m_box.w / 2, m_box.y + 15, NULL, NULL, true,  true );
        game->drawTexture( "TEXT_TOOLTIP_ENEMY_STATS_HPS",  m_box.x + 8,  m_box.y + 50,          NULL, NULL, false, true );
        game->drawTexture( "TEXT_TOOLTIP_ENEMY_STATS_WTH",  m_box.x + 8,  m_box.y + 70,          NULL, NULL, false, true );
        game->drawTexture( "TEXT_TOOLTIP_ENEMY_STATS_SPD",  m_box.x + 8,  m_box.y + 90,          NULL, NULL, false, true );
        game->drawTexture( m_enemyHpsAdrs,                  m_box.x + 80, m_box.y + 50,          NULL, NULL, false, true );
        game->drawTexture( m_enemyWthAdrs,                  m_box.x + 80, m_box.y + 70,          NULL, NULL, false, true );
        game->drawTexture( m_enemySpdAdrs,                  m_box.x + 80, m_box.y + 90,          NULL, NULL, false, true );
    }
}
