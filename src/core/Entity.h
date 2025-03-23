#ifndef ENTITY_H
#define ENTITY_H


#include "Vec2.h"
#include "Vec2f.h"


class Entity{

protected:
    Vec2 position;
    Vec2 dimension;
    Vec2f velocity;

public:
    Entity();
    Entity(int x, int y, int w, int h, float vx, float vy);
    Entity(Vec2 pos, Vec2 dim, Vec2f vel);

    virtual ~Entity();

    virtual void update() = 0;

    Vec2 getPos() const {return position;}
    Vec2 getDim() const {return dimension;}
    
    bool checkCollision(const Entity& other) const;

    
        
};



#endif