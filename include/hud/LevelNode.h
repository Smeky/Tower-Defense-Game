#ifndef LEVELNODE_H
#define LEVELNODE_H

#include "IButton.h"

class LevelNode : public IButton {
public:
    LevelNode( SDL_Rect box, int id );
private:
};

#endif // LEVELNODE_H
