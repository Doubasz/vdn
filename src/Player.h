#ifndef PLAYER_H
#define PLAYER_H

#include "Vec2.h"
#include "Vec2f.h"

enum Etat{
    QAHWA,
    ZETLA,
};

enum PlayerState{
    NEUTRAL,
    JUMP,
};

#define ACCEL 0.5f
#define FRICTION 0.3f
#define GRAVITY 0.8f
#define MAX_SPEED 5.0f


class Player{

    Vec2 position;
    Vec2f velocity;

    float accel;
    float friction;
    int munition;
    int state;

    public:
        Player();

        void sauter();
        void lancerPierre();
        //void seDeplacer(const Uint8* key);
        //void draw(SDL_Renderer* renderer);
        void changePosition(Vec2 pos);
        void updateGravity();
        void resetGravity();
        void update();

};



#endif