


#include "Entity.h"




Entity::Entity(){
    position = {0, 0};
    dimension = {0, 0};
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


bool Entity::checkCollision(const Entity& other) const{
    return (position.x < other.position.x + other.dimension.x &&
            position.x + dimension.x > other.position.x &&
            position.y < other.position.y + other.dimension.y &&
            position.y + dimension.y > other.position.y);
}