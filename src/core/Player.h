#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Timer.h"

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
    float frictionAir;
    float maxSpeed;
    float maxFall;
    float gravity;
    float jumpBoost;
    int munition;
    int state;

    Timer moveTimer;

public:
    Player();

    void sauter();

    void seDeplacer(std::string input);

    void changePosition(Vec2 pos);
    void changePosition(int x, int y);

    void changeVelocity(int x, int y);

    bool checkCollisionPlatform(Entity& platform);

    void checkCollisionEnnemy(Entity& ennemy);

    void updateGravity();
    void resetGravity();

    void update() override;

    int getState();
    void setJumpBoost(int j);
    void goLeft();
    void goRight();
    void sufferFriction();

    void setState(int s){this->state = s;}

};

bool contains(std::string input, char target);

#endif 