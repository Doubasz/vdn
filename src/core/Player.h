#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

enum Etat{
    QAHWA,
    ZETLA,
};

enum PlayerState{
    NEUTRAL,
    LEFT,
    RIGHT,
    JUMP,
};




#define ACCEL 0.5f
#define FRICTION 0.3f
#define GRAVITY 0.8f
#define MAX_SPEED 5.0f


class Player : public Entity{


private:
    float accel;
    float friction;
    float maxSpeed;
    float maxFall;
    float gravity;
    int munition;
    int jumpBoost;
    int state;

public:
    Player();

    void sauter();

    void seDeplacer(std::string input);

    void changePosition(Vec2 pos);
    void changePosition(int x, int y);

    void changeVelocity(int x, int y);

    void updateGravity();
    void resetGravity();

    void update() override;

    int getState();
    void setJumpBoost(int j);

};

bool contains(std::string input, char target);

#endif