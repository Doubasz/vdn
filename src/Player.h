#ifndef PLAYER_H
#define PLAYER_H

#include "Draw.h"

enum Etat{
    QAHWA,
    ZETLA,
};


class Player{

    SDL_Rect rect;
    SDL_Texture* texture;

    int gravity;
    int velocity;
    int accel;
    int munition;
    int etat;

    public:
        Player();

        SDL_Rect getRect();

        void sauter();
        void lancerPierre();
        void seDeplacer(SDL_Keycode key);
        void draw(SDL_Renderer* renderer);
        void changePosition(Vec2 pos);
        void updateGravity();
        void resetGravity();

};



#endif