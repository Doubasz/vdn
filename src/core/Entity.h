#ifndef ENTITY_H
#define ENTITY_H


#include "Vec2.h"
#include "Vec2f.h"

#include "Shapes.h"
#include <algorithm>


enum Directions{
    LEFT,
    RIGHT,
    UP,
    DOWN,
};



class Entity{

public:
    Rectangle box;

    int hp;
    bool isAlive;
    float iFrames;
    float iFramesTimer;
    bool canGetHit;
    bool isVisible;

protected:

    Vec2f velocity;

    bool onGround;

    float knockBackTimer;
    float knockBackDuration;
    float knockBackForce;
    float knockBackFriction;
    bool onKnockBack;

public:
    Entity();
    Entity(int x, int y, int w, int h, float vx, float vy);
    Entity(Vec2 pos, Vec2 dim, Vec2f vel);

    virtual ~Entity();


    Vec2f getVel() const {return velocity;}

    void setPos(int x, int y);
    void setDim(int x, int y);
    void setVel(int x, int y);

    void setHp(int h);
    int getHp();
    void decreaseHp();
    void increaseHp();
    
    bool checkCollision(const Entity& other) const ;
    bool checkCollisionWithTop(const Entity& other);
    
    void updateIFrames(float deltaTime);
    void updateKnockBack(float deltaTime);

    void applyKnockBack(float force, float duration);

    Rectangle getBox() const {return this->box;}
    bool getIsVisible() const {return this->isVisible;}

    void setOnGround(int b) {this->onGround = b;}
};


#endif