


#include "Entity.h"




Entity::Entity(){
    position = {0, 0};
    dimension = {1, 1};
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
    int left1 = position.x;
    int right1 = position.x + dimension.x;
    int top1 = position.y;
    int bottom1 = position.y + dimension.y;

    int left2 = other.position.x;
    int right2 = other.position.x + other.dimension.x;
    int top2 = other.position.y;
    int bottom2 = other.position.y + other.dimension.y;

    // Vérifie si les deux entités se chevauchent (collision)
    if (right1 > left2 && left1 < right2 && bottom1 > top2 && top1 < bottom2) {
        // Collision horizontale (gauche/droite)
        if (right1 > left2 && left1 < left2) {
            position.x = left2 - dimension.x; // Réajuste à gauche
        } 
        else if (left1 < right2 && right1 > right2) {
            position.x = right2; // Réajuste à droite
        }

        // Collision verticale (haut/bas)
        if (bottom1 > top2 && top1 < top2) {
            position.y = top2 - dimension.y; // Réajuste en bas
        } 
        else if (top1 < bottom2 && bottom1 > bottom2) {
            position.y = bottom2; // Réajuste en haut
        }
        
        return true; // Collision détectée
    }
    return false; // Pas de collision
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