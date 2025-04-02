


#include "Entity.h"




Entity::Entity(){
    position = {0, 0};
    dimension = {32, 32};
    velocity = {0, 0};
}

Entity::Entity(int x, int y, int w, int h, float vx, float vy){
    position = {x, y};
    dimension = {w, h};
    velocity = {vx, vy};
}

Entity::Entity(Vec2 pos, Vec2 dim, Vec2f vel){
    position = pos;
    dimension = dim;
    velocity = vel;
}

Entity::~Entity(){}


bool Entity::checkCollision(const Entity& other){
    this->box.overlaps(other.box);
}


void Entity::setPos(int x, int y){
    position = {x, y};
}

void Entity::setDim(int x, int y){
    dimension = {x, y};
}

void Entity::setVel(int x, int y){
    velocity = {x, y};
}