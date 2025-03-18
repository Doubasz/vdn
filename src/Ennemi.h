#ifndef ENNEMI_H
#define ENNEMI_H

#include "Draw.h"

enum Type{
    SCORPION,
    KALB,
};

class Ennemi{

    Vec2 position;
    
    int type;
    SDL_Rect rect;
    SDL_Texture* texture;

    public:
        Ennemi();
        void comportement();
        void drawEnnemi();

};

#endif