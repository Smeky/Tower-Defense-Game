#include "core\SoundManager.h"
#include "core\Engine.h"

#include "iostream"
using namespace std;

void SoundManager::loadMedia( Engine* game ) {
    m_muteSound = false;
    m_muteMusic = false;

    m_uiButton  = Mix_LoadWAV( "media/sounds/uiButton.wav" );
    m_uiError   = Mix_LoadWAV( "media/sounds/uiError.wav" );

    m_turretPlacement    = Mix_LoadWAV( "media/sounds/turretPlacement.wav" );
    m_towerPlasmaShooter = Mix_LoadWAV( "media/sounds/shooterAttack.wav" );
    m_projectRocketHit   = Mix_LoadWAV( "media/sounds/rocketHit.wav" );

    Mix_VolumeChunk( m_towerPlasmaShooter, 16 );
    Mix_VolumeChunk( m_turretPlacement, 32 );
}

void SoundManager::close() {
    Mix_FreeChunk( m_uiButton );
    Mix_FreeChunk( m_uiError );
    Mix_FreeChunk( m_towerPlasmaShooter );
    Mix_FreeChunk( m_turretPlacement );
    Mix_FreeChunk( m_projectRocketHit );
}

void SoundManager::playSound( std::string name ) {
    if( !m_muteSound ) {
             if( name == "UI_BUTTON_PRESS" )        Mix_PlayChannel( -1, m_uiButton, 0 );
        else if( name == "SOUND_UI_ERROR" )         Mix_PlayChannel( -1, m_uiError,  0 );
        else if( name == "ATTACK_PLASMA_SHOOTER" )  Mix_PlayChannel( -1, m_towerPlasmaShooter,  0 );
        else if( name == "TURRET_PLACEMENT" )       Mix_PlayChannel( -1, m_turretPlacement,  0 );
        else if( name == "PROJECTILE_HIT_ROCKET" )  Mix_PlayChannel( -1, m_projectRocketHit,  0 );
    }
}

void SoundManager::playMusic( std::string name ) {
    if( !m_muteMusic ) {
        if( name == "MUSIC_BACKGROUND" ) Mix_PlayMusic( m_backgroundMusic, -1 );
    }
}
