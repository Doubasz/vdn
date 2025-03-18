


#include "Player.h"


Player::Player(){

    position = {0, 0};
    velocity = {0.0, 0.0};
    accel = 1;
    munition = 0;
    state = 0;

}



void Player::changePosition(Vec2 pos){

    position = pos;
}


void Player::sauter(){
    if(state != JUMP){
        velocity.y = -20;
    }
}

void Player::update(){
    position.x += velocity.x;
    position.y += velocity.y;
}


/*void Player::seDeplacer(const Uint8* key){  

    if(key[SDL_SCANCODE_RIGHT] || key[SDL_SCANCODE_D]){
        velocity.x += ACCEL;
        if(velocity.x > MAX_SPEED) velocity.x = MAX_SPEED;
    }
    else if(key[SDL_SCANCODE_LEFT] || key[SDL_SCANCODE_Q]){

        velocity.x -= ACCEL;
        if(velocity.x < -MAX_SPEED) velocity.x = -MAX_SPEED;
    }
    else{
        if(state == NEUTRAL){
            if(velocity.x > 0){
                velocity.x -= FRICTION;
                if(velocity.x < 0) velocity.x = 0;
            }
            if(velocity.x < 0){
                velocity.x += FRICTION;
                if(velocity.x > 0) velocity.x = 0;
        }
        
        }
    }
}*/

void Player::updateGravity(){
    velocity.y += GRAVITY;
    state = JUMP;
}

void Player::resetGravity(){
    velocity.y = 0;
    //rect.y = 700 - rect.h;
    state = NEUTRAL; 
}
