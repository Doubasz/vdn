


#include "Player.h"



Player::Player(): Entity(){

    accel = 1;
    friction = 1;
    maxSpeed = 1;
    maxFall = 15;
    gravity = 1;
    jumpBoost = -10;
    dimension = {1, 1};
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
bool Player::getIsgrounded() const {
    return isgrounded;
}


void Player::setIsgrounded(bool grounded){
isgrounded=grounded;
}

void Player::sauter(){
    if(isgrounded){
        velocity.y = jumpBoost;
        isgrounded = false ;
        state = JUMP;
    }
}

void Player::update(){
    position.x += velocity.x;
    position.y += velocity.y;
}


void Player::checkAndUpdate(std::vector<std::vector<int>> &gameMap) {
    // Vérifier d'abord les limites du tableau
    int mapWidth = gameMap[0].size();
    int mapHeight = gameMap.size();
    
    int newPosX = position.x + velocity.x;
    int newPosY = position.y + velocity.y;
    
    // Vérifier les bords
    if (newPosX < 0 || newPosX >= mapWidth || 
        newPosY < 0 || newPosY >= mapHeight) {
        velocity = {0, 0};
        return;
    }

    // Vérifier les collisions seulement si dans les limites
    if (gameMap[newPosY][newPosX] == 0) {
        velocity = {0, 0};
    } else {
        update();
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
        std::cout << "saute" ;
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

void Player::updateGravity() {
    if (!isgrounded) {
        velocity.y += gravity;
        velocity.y = std::min(velocity.y, maxFall);
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