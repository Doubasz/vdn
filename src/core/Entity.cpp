


#include "Entity.h"




Entity::Entity(){
    velocity = {0, 0};

    knockBackTimer = 0;
    knockBackDuration = 0;
    knockBackForce = 0;
    knockBackFriction = 10;
    onKnockBack = false;

    isVisible = true;
}

Entity::Entity(int x, int y, int w, int h, float vx, float vy){
    velocity = {vx, vy};
}

Entity::Entity(Vec2 pos, Vec2 dim, Vec2f vel){
    velocity = vel;
}

Entity::~Entity(){}


// Dans Entity.cpp
bool Entity::checkCollision(const Entity& other) const {
    return box.overlaps(other.box);
}


bool Entity::checkCollisionWithTop(const Entity& other){
    if(box.overlaps(other.box)){
        if(this->box.bottom - velocity.y <= other.box.top){
            return true;
        }
    }
    return false;
}

void Entity::updateIFrames(float deltaTime){
    if(!canGetHit){
        if(iFramesTimer < iFrames){
            iFramesTimer += deltaTime;
            isVisible = !isVisible;

            if (iFramesTimer >= iFrames){
                iFramesTimer = 0;
                canGetHit = true;
                isVisible = true;
            }
        }
    }
}

void Entity::applyKnockBack(float force, float duration){
    knockBackForce = force;
    knockBackDuration = duration;

    velocity = {0, 0};
}


void Entity::updateKnockBack(float deltaTime){

    if(knockBackTimer < knockBackDuration){
        knockBackTimer += deltaTime;

        if(knockBackTimer >= knockBackDuration){
            knockBackTimer = 0;
            onKnockBack = false;
        }
        else{
            velocity.x += knockBackForce;
            velocity.y -= knockBackForce / 2;
        }
    }

    if(knockBackForce > 0){
        knockBackForce -= knockBackFriction;

        if(knockBackForce < 0) knockBackForce = 0;
    }
}





void Entity::setVel(int x, int y){
    velocity = {x, y};
}

void Entity::setHp(int h){hp = h;}

int Entity::getHp(){return hp;}

void Entity::increaseHp(){hp++;}

void Entity::decreaseHp(){
    hp--;
    if(hp < 0){
        hp = 0;
        isAlive = false;
    }
}