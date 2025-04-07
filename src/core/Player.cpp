


#include "Player.h"



Player::Player(): Entity(), moveTimer(3){

    accel = 1;
    friction = 1;
    maxSpeed = 1;
    maxFall = 0.3125;
    gravity = 0.1;
    frictionAir = 0.25;
    jumpBoost = -1;
    dimension = {1, 1};
    velocity = {0, 0};
    box = Rectangle(0, 0, 1, 1);

    munition = 0;
    state = NEUTRAL;
    moveTimer.reset();
    direction = RIGHT;
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

void Player::updateHorizontalMovement(float deltaTime){
    box.setX(box.x + velocity.x);
}

void Player::updateVerticalMovement(float deltaTime){
    box.setY(box.y + velocity.y);
}

void Player::checkHorizontalCollision(Entity& platform){

    float prevRight = this->box.rightMost - velocity.x;
    float prevLeft = this->box.leftMost - velocity.x;

    // Moving right into platform
    if(this->box.overlaps(platform.box)){
        if (velocity.x > 0 && prevRight <= platform.box.leftMost) {
            this->box.setX(platform.box.leftMost - (this->box.w + .001));
            velocity.x = 0;

            std::cout << "Collided with left of platform : " << platform.box.toString() << std::endl;
        } 
        // Moving left into platform
        else if (velocity.x < 0 && prevLeft >= platform.box.rightMost) {
            this->box.setX(platform.box.rightMost + .001);
            velocity.x = 0;

            std::cout << "Collided with right of platform : " << platform.box.toString() << std::endl;
        }
    }
    
}

bool Player::checkVerticalCollision(Entity& platform){
    // No collision at all
    if (!this->box.overlaps(platform.box)) {
        return false;
    }
    
    // Calculate how much player overlaps with each side of the platform
    float overlapTop = this->box.bottom - platform.box.top;
    float overlapBottom = platform.box.bottom - this->box.top;
    float overlapLeft = this->box.rightMost - platform.box.leftMost;
    float overlapRight = platform.box.rightMost - this->box.leftMost;
    
    // Previous frame positions
    bool wasAbove = (this->box.bottom - velocity.y) <= platform.box.top;
    bool wasBelow = (this->box.top - velocity.y) >= platform.box.bottom;
    bool wasLeftOf = (this->box.rightMost - velocity.x) <= platform.box.leftMost;
    bool wasRightOf = (this->box.leftMost - velocity.x) >= platform.box.rightMost;
    
    // IMPORTANT: First check if player was above before any other collision
    if (wasAbove) {
        this->box.setY(platform.box.top - this->box.h);
        velocity.y = 0;
        state = NEUTRAL;
        return true; // Player is on ground
    }
    
    // Only check other collisions if player was NOT above
    if (wasBelow) {
        this->box.setY(platform.box.bottom);
        velocity.y = 0;
    } else if (wasLeftOf) {
        this->box.setX(platform.box.leftMost - this->box.w);
        velocity.x = 0;
    } else if (wasRightOf) {
        this->box.setX(platform.box.rightMost);
        velocity.x = 0;
    }
    
    return false; // Not on ground for other collisions

}


void Player::seDeplacer(std::string input){

    if(contains(input, 'd')){
        if(moveTimer.canProceed() || moveTimer.last_input != 'd'){
            velocity.x += accel;
            if(velocity.x > maxSpeed) velocity.x = maxSpeed;
            moveTimer.reset();

        }
        direction = RIGHT;
    }
    if(contains(input, 'q')){
        if(moveTimer.canProceed() || moveTimer.last_input != 'q'){
        velocity.x -= accel;
        if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;
        moveTimer.reset();
        }
        direction = LEFT;
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

    /*else if(state == JUMP){
        if(velocity.x > 0){
            velocity.x -= frictionAir;
            if(velocity.x < 0) velocity.x = 0;
        }
        if(velocity.x < 0){
            velocity.x += frictionAir;
            if(velocity.x > 0) velocity.x = 0;
        }
            
    }*/
        
    
        
    
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


bool Player::checkPlatformCollision(Entity& platform){

    bool onGround = false;
    
   
    if(this->box.overlaps(platform.box)){
        if(this->box.bottom - velocity.y <= platform.box.top){
            this->box.setY(platform.box.top - this->box.h);
            velocity.y = 0;
            state = NEUTRAL;
            onGround = true;
            
            //std::cout << "Collided with top of platform : " << platform.box.toString() << std::endl;
            //std :: cout << "player pos : " << this->box.toString() << std::endl;
        }
        else if(this->box.rightMost - velocity.x <= platform.box.leftMost){
           this->box.setX(platform.box.leftMost - (this->box.h + 0.01));
            velocity.x = 0;

            std::cout << "Collided with left of platform : " << platform.box.toString() << std::endl;
            std :: cout << "player pos : " << this->box.toString() << std::endl;
        }
        else if(this->box.leftMost - velocity.x >= platform.box.rightMost){
            this->box.setX(platform.box.rightMost + 0.01);
            velocity.x = 0;
            //std::cout << "Collided with right of platform : " << platform.box.toString() << std::endl;
        }
        else if(this->box.top - velocity.y >= platform.box.bottom ){
            this->box.setY(platform.box.bottom);
            velocity.y = 0;

            std::cout << "Collided with bottom of platform : " << platform.box.toString() << std::endl;
        }
    }

    return onGround;
}

void Player::checkCollisionEnnemy(Entity& ennemy){

        if(this->checkCollision(ennemy)){
            this->box.setX(5);
            this->box.setY(5);
        }

    
}