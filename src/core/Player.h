#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Timer.h"

enum Etat{
    QAHWA,
    ZETLA,
};


enum PlayerState{
    IDLE,
    RUNNING,
    JUMP,
    FALLING,
    ATTACK,
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

    bool onGround;
    
    int direction;
    int state;

    bool isJumpButtonHeld = false;
    float jumpHoldTime;
    float maxJumpHoldTime;
    float minJumpBoost;
    float maxJumpBoost;

    Rectangle attackHitBox;
    bool isAttacking;
    bool onCoolDown;
    float attackWindow;
    float attackTimer;
    float attackCooldown;

    bool gotHit;
    float blinkInterval;


    Timer moveTimer;
    
    


public:
    Player();

    void jump();
    void releaseJump();
    void updateJump(float deltaTime);

    void seDeplacer(std::string input);

    void attack();
    void updateAttack(float deltaTime);

    void changePosition(Vec2 pos);
    void changePosition(int x, int y);

    void changeVelocity(int x, int y);

    bool checkPlatformCollision(Entity& platform);

    void checkCollisionEnnemy(Entity& ennemy, float deltaTime);

    void updateGravity();
    void resetGravity();

    void update(float deltaTime);
    void updateState();
    void updateHorizontalMovement(float deltaTime);
    void updateVerticalMovement(float deltaTime);

    void checkHorizontalCollision(Entity& platform);
    bool checkVerticalCollision(Entity& platform);

    int getState();
    void setJumpBoost(int j);
    void goLeft();
    void goRight();
    void sufferFriction();

    int getDirection() {return this->direction;}
    bool getGotHit() {return this->gotHit;}
    bool getCanGetHit() {return this->canGetHit;}
    
    void setState(int s){this->state = s;}
    void setGotHit(int b) {this->gotHit = b;}
    void setOnGround(int b) {this->onGround = b;}

    Rectangle& getAttackHitBox() {return this->attackHitBox;}



};

bool contains(std::string input, char target);

#endif