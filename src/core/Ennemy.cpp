#include "Ennemy.h"





Ennemy::Ennemy() : Entity(), move(0.5){
    velocity = {1, 0};
    box = {0,0,1,1};
    
    maxFall = 15.3125;
    gravity = 0;

    direction = RIGHT;
    isAlive = true;
    iFrames = 0.4f;
    iFramesTimer = 0;
    hp = 2;
    
    move.reset();
}

Ennemy::Ennemy(int x, int y,int typeEnnemie) : Ennemy(){
    box.setX(x);
    box.setY(y);
    type = typeEnnemie;
}

void Ennemy::changePosition(int x, int y) {
    box.setX(x);
    box.setY(y);
}
void Ennemy::update(float deltaTime) {

    updateIFrames(deltaTime);
    velocity.y += gravity;


    box.setX(box.x + (velocity.x * deltaTime ));
    box.setY(box.y + (velocity.y * deltaTime ));
    
    direction = (velocity.x < 0) ? LEFT : RIGHT;
}

void Ennemy::changeDirection(){
    velocity.x = -velocity.x;
}


int Ennemy::getType() const {
    return type;
}
bool Ennemy::PlayerOutofRange(Entity& player) const {
    float playerPosX = player.getBox().x;
    float enemyPosX = this->box.x;
    float distanceX = playerPosX - enemyPosX;
    
    
    const float followRange = 5 ; // Example range

   
    return (!(abs(distanceX) <= followRange));
}
void Ennemy::followPlayer(Entity& player) {
    float playerPosX = player.getBox().x;
    float enemyPosX = this->box.x;

    float distanceX = playerPosX - enemyPosX;
    
    
   
    if (!PlayerOutofRange(player)) {
       
        // Determine direction and change its direction if necessary
        // Player is to the right, move right
        if (distanceX > 0) {

            if(velocity.x < 0)
                changeDirection();

        //player is to the left move left
        } else if (distanceX < 0) {

            if(velocity.x > 0)
                changeDirection();
        }
    }
}

bool Ennemy::hitWall(Entity & platform){

    bool onGround = false;
    
   
    if(this->box.overlaps(platform.box)){
        if(this->box.bottom - velocity.y <= platform.box.top){
            this->box.setY(platform.box.top - (this->box.h));
            velocity.y = 0;
            onGround = true;

        }
        else if(this->box.rightMost - velocity.x  <= platform.box.leftMost){
            this->box.setX(platform.box.leftMost - (this->box.h));
            
            return true;
        }
        else if(this->box.leftMost - velocity.x  >= platform.box.rightMost){
            this->box.setX(platform.box.rightMost );
           
            return true;
        }
    
    }

    return false;
    
}
bool Ennemy::vaTomber(std::vector<std::vector<int>> &gameMap) {
    Rectangle nextpos = {this->box.x + velocity.x ,this->box.y + 1,1,1};
    if(gameMap[nextpos.y][nextpos.x] == -1)//NONE
        return true;
    return false;


}

