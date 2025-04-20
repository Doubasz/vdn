


#include "Player.h"



Player::Player(): Entity(), moveTimer(3){

    hp = 5;
    isAlive = true;

    accel = 1;
    friction = 1;
    maxSpeed = 10;
    maxFall = 15.3125;
    gravity = 1.;
    frictionAir = 0.25;

    jumpHoldTime = 0.0f;
    maxJumpHoldTime = 0.4f;
    minJumpBoost = -1.f;
    maxJumpBoost = -10.f;

    onGround = true;

    velocity = {0, 0};
    box = Rectangle(0, 0, 1, 1);

    attackWindow = 0.3f;
    attackTimer = 0;
    attackCooldown = 0.2f;
    onCoolDown = false;

    iFrames = 1.5f;
    iFramesTimer = 0;
    canGetHit = true;



    gotHit = false;

    blinkInterval = iFrames;

    state = IDLE;
    moveTimer.reset();
    direction = RIGHT;
}


bool Player::getOnGround() const {
    return onGround;
}
bool Player::getGotHit()const {
    return gotHit;
}


void Player::changePosition(int x, int y){
    box.setX(x);
    box.setY(y);
}
bool Player::getIsAlive() const {
    return isAlive;
}
void Player::jump(){
    if(onGround){
        onGround = false;
        velocity.y = minJumpBoost;
        state = JUMP;
        isJumpButtonHeld = true;
        jumpHoldTime = 0;
    }
}

void Player::releaseJump(){
    isJumpButtonHeld = false;
}

void Player::updateJump(float deltaTime){

    if(!onGround && isJumpButtonHeld){
        jumpHoldTime += deltaTime;

        if(jumpHoldTime >= maxJumpHoldTime){
            isJumpButtonHeld = false;
            jumpHoldTime = maxJumpHoldTime;
        }

        float jumpProgress = jumpHoldTime / maxJumpHoldTime;
        float targetVelocity = minJumpBoost + (maxJumpBoost - minJumpBoost) * 1;//jumpProgress;

        if(velocity.y > targetVelocity){
            velocity.y = targetVelocity;
        }
 
        
    }
}


void Player::update(float deltaTime){
    
    updateKnockBack(deltaTime);
    updateIFrames(deltaTime);
    updateAttack(deltaTime);
    updateJump(deltaTime);

    box.setX(box.x + velocity.x * deltaTime);
    box.setY(box.y + velocity.y * deltaTime);
    
    updateState();

    
}




void Player::updateState(){
    if(velocity.x == 0 && velocity.y == 0){
        state = IDLE;
    }
    if(velocity.y > 0 && !onGround){
        state = FALLING;
    }
    if(velocity.y < 0 && !onGround){
        state = JUMP;
    }
    if(isAttacking){
        state = ATTACK;
    }
}



void Player::seDeplacer(std::string input){

    static bool wasSpacePressed = false;
    static bool wasAttackPressed = false;

    bool isAttackPressed = contains(input, 'm');
    bool isSpacePressed = contains(input, ' ');

    if(contains(input, 'd')){
        
        velocity.x += accel;
        if(velocity.x > maxSpeed) velocity.x = maxSpeed;
        state = RUNNING;

        direction = RIGHT;
    }
    if(contains(input, 'q')){

        velocity.x -= accel;
        if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;
        state = RUNNING;
        
        direction = LEFT;
    }

    if(isAttackPressed){
        attack();
    }



    if(isSpacePressed && !wasSpacePressed){
        jump();
    }

    else if(!isSpacePressed && wasSpacePressed && !onGround){
        releaseJump();
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
    wasSpacePressed = isSpacePressed;    
    
}


void Player::attack(){

    if(!isAttacking && !onCoolDown){
        isAttacking = true;
        attackTimer = attackWindow;

        Rectangle temp;

        switch(direction){
            case LEFT:
                temp = {(box.leftMost - box.w - 0.5), box.top, 1, 1};
                break;
            case RIGHT:
                temp = {box.rightMost + 0.5, box.top, 1, 1};
            case UP:
            case DOWN:
                break;
        }

        attackHitBox = temp;
    }
}

void Player::updateAttack(float deltaTime){

    if(onCoolDown){
        attackTimer -= deltaTime;

        if(attackTimer <= 0){
            onCoolDown = false;
        }
    }
    else{
        if(attackTimer > 0){
            attackTimer -= deltaTime;
    
            if(attackTimer <= 0){
                isAttacking = false;
                onCoolDown = true;
                attackTimer = attackCooldown;
                attackHitBox = {0, 0, 0, 0};
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
    if(!onGround){
        velocity.y += gravity;
        if(velocity.y > maxFall) velocity.y = maxFall;
    }
    
}

void Player::resetGravity(){
    onGround = true; 
    velocity.y = 0;
    //rect.y = 700 - rect.h;
}


int Player::getState(){
    return state;
}

void Player::setJumpBoost(int j){
    maxJumpBoost = j;
}



bool Player::checkPlatformCollision(Entity& platform) {
    bool onGroundRet = false;
    bool debugOutput = false;
    
    // First check if there's an overlap
    if (this->box.overlaps(platform.box)) {
        // Calculate previous position based on velocity
        float prevX = this->box.leftMost - velocity.x;
        float prevY = this->box.top - velocity.y;
        
        // Calculate overlap amounts in each direction
        float overlapLeft = this->box.rightMost - platform.box.leftMost;
        float overlapRight = platform.box.rightMost - this->box.leftMost;
        float overlapTop = this->box.bottom - platform.box.top;
        float overlapBottom = platform.box.bottom - this->box.top;
        
        // Determine minimum overlap
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);
        
        // Determine if collision is more horizontal or vertical based on
        // both overlap and velocity direction
        bool resolveHorizontal = false;
        
        // Check if we were approaching more from horizontal or vertical direction
        if (minOverlapX < minOverlapY) {
            resolveHorizontal = true;
        } else if (minOverlapX > minOverlapY) {
            resolveHorizontal = false;
        } else {
            // If overlaps are equal, use velocity to determine direction
            resolveHorizontal = std::abs(velocity.x) > std::abs(velocity.y);
        }
        
        if (resolveHorizontal) {
            // Horizontal collision resolution
            if (overlapLeft < overlapRight) {
                // Collision from left side
                this->box.setX(platform.box.leftMost - (this->box.w + 0.01));
                velocity.x = 0;
                if (debugOutput) {
                    std::cout << "Collided with left of platform: " << platform.box.toString() << std::endl;
                    std::cout << "Player pos: " << this->box.toString() << std::endl;
                }
            } else {
                // Collision from right side
                this->box.setX(platform.box.rightMost + 0.01);
                velocity.x = 0;
                if (debugOutput) {
                    std::cout << "Collided with right of platform: " << platform.box.toString() << std::endl;
                    std::cout << "Player pos: " << this->box.toString() << std::endl;
                }
            }
        } else {
            // Vertical collision resolution
            if (overlapTop < overlapBottom) {
                // Collision from top (player is on ground)
                this->box.setY(platform.box.top - this->box.h);
                velocity.y = 0;
                onGround = true;
                onGroundRet = true;
                if (debugOutput) {
                    std::cout << "Collided with top of platform: " << platform.box.toString() << std::endl;
                    std::cout << "Player pos: " << this->box.toString() << std::endl;
                }
            } else {
                // Collision from bottom (player hit ceiling)
                this->box.setY(platform.box.bottom);
                velocity.y = 0;
                if (debugOutput) {
                    std::cout << "Collided with bottom of platform: " << platform.box.toString() << std::endl;
                    std::cout << "Player pos: " << this->box.toString() << std::endl;
                }
            }
        }
    }
    
    return onGroundRet;
}



void Player::checkCollisionEnnemy(Entity& ennemy, float deltaTime){

    if(this->attackHitBox.overlaps(ennemy.box)){

        if(ennemy.canGetHit){

            ennemy.decreaseHp();
            ennemy.canGetHit = false;

            switch(direction){
                case RIGHT:
                    ennemy.box.setX(ennemy.box.x + 2);
                    
                    break;
                case LEFT:
                    ennemy.box.setX(ennemy.box.x - 2);
                    break;
            }   
        }
    }

    if(this->checkCollision(ennemy)){
        if(canGetHit){
            this->decreaseHp();

            canGetHit = false;
            gotHit = true;

            applyKnockBack(15, 0.3);
        }
    }
}

