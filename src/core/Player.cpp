


#include "Player.h"



Player::Player(): Entity(){

    accel = 1;
    friction = 1;
    maxSpeed = 5;
    maxFall = 10;
    gravity = 1.5;
    jumpBoost = -20;
    dimension = {32, 32};
    velocity = {0, 0};
    box = Rectangle(0, 0, 32, 32);

    munition = 0;
    state = NEUTRAL;
}



void Player::changePosition(Vec2 pos){
    position = pos;
    box.setX(pos.x);
    box.setY(pos.y);
}

void Player::changePosition(int x, int y){
    position = {x, y};
    box.setX(x);
    box.setY(y);
}

void Player::sauter(){
    if(state != JUMP){
        velocity.y = jumpBoost;
        state = JUMP;
    }
}

void Player::update(float deltaTime){
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    box.setX(box.x + velocity.x);
    box.setY(box.y + velocity.y);
}

void Player::goLeft(){
    velocity.x -= accel;
    if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;
}

void Player::goRight(){
    velocity.x += accel;
    if(velocity.x > maxSpeed) velocity.x = maxSpeed;
}

void Player::sufferFriction(){

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


void Player::seDeplacer(std::string input){

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
    if(state != NEUTRAL){
        velocity.y += gravity;
        if(velocity.y > maxFall) velocity.y = maxFall;
    }
    
}

void Player::resetGravity(){
    velocity.y = 0;
    //rect.y = 700 - rect.h;
    state = NEUTRAL; 
}


int Player::getState(){
    return state;
}

void Player::setJumpBoost(int j){
    jumpBoost = j;
}


bool Player::checkCollisionPlatform(Entity& platform){

    bool onGround = false;

    if(this->box.overlaps(platform.box)){
        if(this->box.bottom - velocity.y <= platform.box.top){
            this->box.setY(platform.box.top - this->box.h);
            velocity.y = 0;
            state = NEUTRAL;
            onGround = true;

            std::cout << "Collided with top of platform : " << platform.box.toString() << std::endl;
        }
        else if(this->box.top - velocity.y >= platform.box.bottom){
            this->box.setY(platform.box.bottom);
            velocity.y = 0;

            std::cout << "Collided with bottom of platform : " << platform.box.toString() << std::endl;
        }
        else if(this->box.rightMost - velocity.x <= platform.box.leftMost){
            this->box.setX(platform.box.leftMost - (this->box.h + 1));
            velocity.x = 0;

            std::cout << "Collided with left of platform : " << platform.box.toString() << std::endl;
        }
        else if(this->box.leftMost - velocity.x >= platform.box.rightMost){
            this->box.setX(platform.box.rightMost + 1);
            velocity.x = 0;

            std::cout << "Collided with right of platform : " << platform.box.toString() << std::endl;
        }
    }

    return onGround;
}