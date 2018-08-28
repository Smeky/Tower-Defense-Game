#include "core\Engine.h"
#include "PlayState.h"
#include "MenuState.h"

int main()
{
    Engine game;

    if( !game.init() ) {
        return 0;
    }

    game.changeState( MenuState::instance() );

    while( game.isRunning() ) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.close();

    return 0;
}
