


#include "Player.h"



Player::Player(){

    position = {1, 1};
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



 void Player::seDeplacer(const char key, const Niveau &niv){  

    if(key == 'D' || key == 'd' ){
       
        if(niv.estPositionPersoValide(position.x + 1,position.y))
            position.x += 1;
        
    }
    else if( key == 'Q' || key == 'q'){

        if(niv.estPositionPersoValide(position.x - 1,position.y))
            position.x -=1;
        
        
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
