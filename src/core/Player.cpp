


#include "Player.h"



Player::Player(): Entity(){

    accel = 1;
    friction = 1;
    maxSpeed = 1;
    maxFall = 1;
    gravity = 1;
    dimension = {0, 0};
    velocity = {0, 0};

    munition = 0;
    state = NEUTRAL;
}



void Player::changePosition(Vec2 pos){
    position = pos;
}

void Player::changePosition(int x, int y){
    position = {x, y};
}

void Player::sauter(){
    if(state != JUMP){
        velocity.y -= 2;
        state = JUMP;
    }
}

void Player::update(){
    position.x += velocity.x;
    position.y += velocity.y;
}


void Player::seDeplacer(std::string input){

    std::cout << "input: " << input << std::endl;

    if(contains(input, 'd')){
        velocity.x += accel;
        if(velocity.x > maxSpeed) velocity.x = maxSpeed;
    }
    if(contains(input, 'q')){
        velocity.x -= accel;
        if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;
    }
    if(contains(input, ' ')){
        sauter();
    }
    
    if(!(contains(input, 'd')  || contains(input, 'q'))){

        if(state == NEUTRAL){
            if(velocity.x > 0){
                velocity.x -= friction;
                if(velocity.x < 0) velocity.x = 0;
            }
            if(velocity.x < 0){
                velocity.x += friction;
                if(velocity.x > 0) velocity.x = 0;
            }
                
        }
    }
        
    
}


void Player::changeVelocity(int x, int y){
    velocity = {x, y};
}


bool contains(std::string s, char target){

    for(char c : s){
        if(c == target) return true;
    }
    return false;
}

void Player::updateGravity(){
    velocity.y += gravity;
    if(velocity.y > maxFall) velocity.y = maxFall;
}

void Player::resetGravity(){
    velocity.y = 0;
    //rect.y = 700 - rect.h;
    state = NEUTRAL; 
}


int Player::getState(){
    return state;
}