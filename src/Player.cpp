


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

Vec2 Player::getPos(){
    return position;
}

void Player::sauter(){
    if(state != JUMP){
        velocity.y -=3;
    }
}

void Player::update(){
    position.x += velocity.x;
    position.y += velocity.y;
}


 void Player::seDeplacer(const char key){  

    if(key == 'D' || key == 'd' ){
        velocity.x += 1;
        if(velocity.x > MAX_SPEED) velocity.x = MAX_SPEED;
    }
    else if( key == 'Q' || key == 'q'){

        velocity.x -= 1;
        if(velocity.x < -MAX_SPEED) velocity.x = -MAX_SPEED;
    }
    
}

void Player::updateGravity(){
    velocity.y += GRAVITY;
    state = JUMP;
}

void Player::resetGravity(){
    velocity.y = 0;
    //rect.y = 700 - rect.h;
    state = NEUTRAL; 
}
