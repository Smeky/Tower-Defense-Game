#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SDL_mixer.h"
#include "map"
#include "string"

class Engine;

class SoundManager {
public:
    void loadMedia( Engine* game );
    void close();
    void playSound( std::string name );
    void playMusic( std::string name );
    void muteSound( bool mute ) { m_muteSound = mute; }
    void muteMusic( bool mute ) { m_muteMusic = mute; }
private:
    bool m_muteSound;
    bool m_muteMusic;
    Mix_Chunk* m_uiButton;
    Mix_Chunk* m_uiError;
    Mix_Chunk* m_towerPlasmaShooter;
    Mix_Chunk* m_turretPlacement;
    Mix_Chunk* m_projectRocketHit;
    Mix_Music* m_backgroundMusic;
    std::map<std::string,Mix_Chunk*> m_sounds;
};

#endif // SOUNDMANAGER_H
