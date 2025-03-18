#ifndef DECOR_H
#define DECOR_H

#include "Draw.h"

class Decor{

    Vec2 position;
    
    SDL_Rect rect;
    SDL_Texture* texture;

    public:
        Decor();
        void draw();

        SDL_Rect getRect();
};


#endif