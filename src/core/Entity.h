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

    Vec2 position;
    Vec2 dimension;
    Vec2f velocity;

public:
    Entity();
    Entity(int x, int y, int w, int h, float vx, float vy);
    Entity(Vec2 pos, Vec2 dim, Vec2f vel);

    virtual ~Entity();


    Vec2 getPos() const {return position;}
    Vec2 getDim() const {return dimension;}
    Vec2f getVel() const {return velocity;}

    void setPos(int x, int y);
    void setDim(int x, int y);
    void setVel(int x, int y);

    void setHp(int h);
    int getHp();
    void decreaseHp();
    void increaseHp();
    
    bool checkCollision(const Entity& other) ;
    bool checkCollisionWithTop(const Entity& other);
    
    void updateIFrames(float deltaTime);

    Rectangle getBox() const {return this->box;}
    bool getIsVisible() const {return this->isVisible;}
    
};


#endif